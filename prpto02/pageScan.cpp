#include "pageScan.h"
#include "mainwin.h"
#include "optical_.h"
#include "disparity.h"

#include <qdebug.h>

#include <qfiledialog.h>
#include <qtextstream.h>
#include <qmessagebox.h>

PageScan::PageScan() {
	m_QMainWin = nullptr;
	m_OptTracker = nullptr;

	m_IsCapturing = false;
	m_IsProc = false;
	m_SetStdFrame = false;
	m_GrabProc = false;

	m_DownScaleOptical = 0.25;
	m_DownScaleDisparity = 0.25;
	m_WinBlockSize = 5;

	m_OptionFolder.setPath(m_OptionFolder.currentPath() + "/conf");
	m_OptionFile.setFileName(m_OptionFolder.path() + "/options.txt");

	if (!m_OptionFolder.exists())
		m_OptionFolder.mkpath(m_OptionFolder.path());
	if (m_OptionFile.exists()) {
		m_OptionFile.open(QIODevice::ReadOnly | QIODevice::Text);

		QTextStream input(&m_OptionFile);
		input >> m_DownScaleOptical >> m_DownScaleDisparity >> m_WinBlockSize;
		m_OptionFile.close();
	} else {
		m_OptionFile.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream out(&m_OptionFile);
		out << "0.25 0.25 5" << endl;
		m_OptionFile.close();
	}

	m_OptTracker	= new jun::Tracker(m_DownScaleOptical);
	m_DMaker = new jun::DisparityMaker(m_DownScaleDisparity);
}

PageScan::~PageScan() {
	m_OptionFile.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&m_OptionFile);
	out << m_DownScaleOptical << " " << m_DownScaleDisparity << " " << m_WinBlockSize << endl;
	m_OptionFile.close();

	cleanUp();
	closeCam();

	if(m_OptionFile.isOpen())
		m_OptionFile.close();

	if (m_OptTracker)
		delete m_OptTracker;
	if (m_DMaker)
		delete m_DMaker;

	m_OptTracker = nullptr;
	m_DMaker = nullptr;
	
	m_QMainWin = nullptr;
}

void PageScan::setUp(MainWin * qMainWindow) {
	m_QMainWin = qMainWindow;
	ui.setupUi(m_QMainWin);
	m_QMainWin->resize(0, 0);
	ui.openGLWidget->setInit(m_OptTracker, m_DMaker);

	ui.btn_clear->setEnabled(false);
	ui.btn_save->setEnabled(false);
	ui.btn_stop->setEnabled(false);
	
	// ui event
	connect(ui.btn_start, &QPushButton::clicked, this, &PageScan::startScan);
	connect(ui.btn_stop, &QPushButton::clicked, this, &PageScan::pause);
	connect(ui.btn_clear, &QPushButton::clicked, this, &PageScan::cleanUp);
	connect(ui.btn_save, &QPushButton::clicked, this, &PageScan::saveFile);

	// menu event
	connect(ui.menuQuit, &QAction::triggered, this, &PageScan::quitWindow);
	connect(ui.menuBack, &QAction::triggered, this, &PageScan::back);
	connect(ui.menuOptions, &QAction::triggered, this, &PageScan::openOptionDialog);
	connect(ui.menuColor, &QAction::triggered, this, &PageScan::changeColor);
	connect(ui.menuView_Box, &QAction::triggered, this, &PageScan::changeVB);


	connect(this, &PageScan::testtest, this, &PageScan::cameraOpenFail);

	startCam();
}

void PageScan::videoRun(int idx) {

	cv::VideoCapture Cam(idx);
	if (!Cam.isOpened()) {
		testtest();
		return;
	}

	int x = ui.lb_cam->size().width();
	int y = ui.lb_cam->size().height();

	while (m_IsCapturing) {
		Cam >> m_Frame;
		cv::resize(m_Frame, m_ResizeFrame, cv::Size(x, y));
		convertMat2Pixmap(m_ResizeFrame, m_QFrame);
		ui.lb_cam->setPixmap(m_QFrame);

		eventProc();

		cv::waitKey(40);
	}
	Cam.release();
}

void PageScan::convertMat2Pixmap(const cv::Mat & src, QPixmap & dst) {
	cv::Mat tmp;
	if (src.channels() == 3) {
		cv::cvtColor(src, tmp, cv::COLOR_BGR2RGB);
		dst.convertFromImage(QImage(tmp.data, src.cols, src.rows, QImage::Format::Format_RGB888));
	} else if (src.channels() == 1) {
		dst.convertFromImage(QImage(src.data, src.cols, src.rows, QImage::Format::Format_Grayscale8));
	}
}

void PageScan::startCam(int idx) {
	if (!m_IsCapturing) {
		m_IsCapturing = true;
		m_CamThread = std::thread([&, idx]() { 
			videoRun(idx);
		});
	}
}

void PageScan::closeCam() {
	m_IsCapturing = false;
	if (m_CamThread.joinable())
		m_CamThread.join();
}

void PageScan::eventProc() {
	m_GrabProc = true;
	if (m_SetStdFrame) {
		m_OptTracker->setStdImg(m_Frame);
		m_StdFrame = m_Frame.clone();
		convertMat2Pixmap(m_ResizeFrame, m_QStdFrame);
		ui.lb_std->setPixmap(m_QStdFrame);

		m_SetStdFrame = false;
		m_IsProc = true;
	} else if (m_IsProc) {
		if (m_OptTracker->processImage(m_Frame)) {
			m_OptTracker->warpAffine(m_Frame, m_CmpFrame);

			double disparity = m_OptTracker->getDisparity();
			if (disparity > 0) {
				m_DMaker->setting(63, m_WinBlockSize, disparity);
				m_DMaker->compute(m_StdFrame, m_CmpFrame);
			} else if (disparity < 0) {
				m_DMaker->setting(63, m_WinBlockSize, -disparity);
				m_DMaker->compute(m_CmpFrame, m_StdFrame);
			}
			cv::resize(m_CmpFrame, m_ResizeFrame, m_ResizeFrame.size());
			convertMat2Pixmap(m_ResizeFrame, m_QFrame);
			ui.lb_cmp->setPixmap(m_QFrame);

			m_Disparity = m_DMaker->getVisFiltedDisparity();
			cv::resize(m_Disparity, m_ResizeFrame, m_ResizeFrame.size());
			convertMat2Pixmap(m_ResizeFrame, m_QFrame);
			ui.lb_disparity->setPixmap(m_QFrame);
			
			m_Reproject = m_DMaker->getVisReprojectMat();
			cv::resize(m_Reproject, m_ResizeFrame, m_ResizeFrame.size());
			convertMat2Pixmap(m_ResizeFrame, m_QFrame);
			ui.lb_reproject->setPixmap(m_QFrame);
		}
	}
	m_GrabProc = false;
}

void PageScan::quitWindow() {
	closeCam();
	m_QMainWin->close();
}

void PageScan::back() {
	cleanUp();
	closeCam();
	m_QMainWin->openPageIntro();
	m_QMainWin->closePageScan();
}

void PageScan::startScan() { 
	cleanUp();

	ui.btn_clear->setEnabled(true);
	ui.btn_stop->setEnabled(true);
	m_SetStdFrame = true;
	ui.menuOptions->setEnabled(false);
}

void PageScan::pause() {
	if (m_IsProc) {
		m_IsProc = false;
		ui.btn_stop->setText("restart");
		ui.btn_save->setEnabled(true);
		ui.menuOptions->setEnabled(true);
	} else {
		m_IsProc = true;
		ui.btn_stop->setText("pause");
		ui.btn_save->setEnabled(false);
		ui.menuOptions->setEnabled(false);
	}
}

void PageScan::cleanUp() {
	ui.btn_clear->setEnabled(false);
	ui.btn_save->setEnabled(false);
	ui.btn_stop->setEnabled(false);
	ui.btn_stop->setText("pause");
	ui.menuOptions->setEnabled(true);

	while (m_GrabProc);
	m_IsProc = false;
	m_SetStdFrame = false;

	m_DMaker->cleanUp();
	m_OptTracker->cleanUp();
	ui.openGLWidget->cleanUp();

	m_QStdFrame = QPixmap(0, 0);
	ui.lb_std->setPixmap(QPixmap(0, 0));
	ui.lb_cmp->setPixmap(QPixmap(0, 0));
	ui.lb_disparity->setPixmap(QPixmap(0, 0));
	ui.lb_reproject->setPixmap(QPixmap(0, 0));

	m_CmpFrame.release();
	m_Disparity.release();
	m_Reproject.release();
	m_StdFrame.release();
}

void PageScan::saveFile() {
	QString selfilter = tr("SCAN (*.scan)");

	QDir saveFolderName = QDir::current().path() + "/save";
	if (!saveFolderName.exists())
		saveFolderName.mkpath(saveFolderName.path());

	QString saveFileName = QFileDialog::getSaveFileName(
		m_QMainWin,
		"save scan file",
		saveFolderName.path(),
		"All files (*.*);;SCAN (*.scan)",
		&selfilter
	);

	if (saveFileName.size() > 0) {
		FILE *fp;
		fopen_s(&fp, saveFileName.toStdString().c_str(), "w");
		if (!fp) {
			QMessageBox::warning(m_QMainWin, "Fail", "failed to create file");
			return;
		}
		cv::Mat xyz		= m_DMaker->getReprojectMat();
		cv::Mat color	= m_DMaker->getReprojectColor();
		
		float *xyzdata = (float *)xyz.data;
		unsigned char *colordata = (unsigned char *)color.data;

		int width = xyz.cols, height = xyz.rows;

		fprintf(fp, "# (*.scan) data format\n");
		fprintf(fp, "# x y z r g b    (z is normalized 0.0-1.0)\n");
		fprintf(fp, "# f f f ub ub ub\n");
		fprintf(fp, "# width %d height %d\n", width, height);
		fprintf(fp, "# vertex_num %d\n", width*height);
		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				fprintf(fp, "%f %f %f %d %d %d\n",
					xyzdata[r*(width * 3) + (c * 3) + 0] * width,
					xyzdata[r*(width * 3) + (c * 3) + 1] * height,
					xyzdata[r*(width * 3) + (c * 3) + 2],
					colordata[r*(width * 3) + (c * 3) + 0],
					colordata[r*(width * 3) + (c * 3) + 1],
					colordata[r*(width * 3) + (c * 3) + 2]);
			}
		}

		fclose(fp);
		QMessageBox::information(m_QMainWin, "save", "the file was saved successfully.");
		return;
	}

}

void PageScan::openOptionDialog() {
	ui_optionDialog.setupUi(&optionDialog);

	int diaX = (m_QMainWin->x() + (m_QMainWin->width() - optionDialog.width()) / 2);
	int diaY = (m_QMainWin->y() + (m_QMainWin->height() - optionDialog.height()) / 2);
	
	optionDialog.move(diaX, diaY);
	ui_optionDialog.trackerspinbox->setValue(m_DownScaleOptical);
	ui_optionDialog.depthspinbox->setValue(m_DownScaleDisparity);
	ui_optionDialog.blocksizepinbox->setValue(m_WinBlockSize);
	connect(ui_optionDialog.buttonBox, &QDialogButtonBox::accepted, this, &PageScan::dialogAccept);
	connect(ui_optionDialog.buttonBox, &QDialogButtonBox::rejected, this, &PageScan::dialogReject);
	optionDialog.show();
}

void PageScan::changeColor() {
	ui.openGLWidget->setColorVertexVisiable(ui.menuColor->isChecked());
}

void PageScan::changeVB() {
	ui.openGLWidget->setViewBoxVisiable(ui.menuView_Box->isChecked());
}

void PageScan::dialogAccept() {
	m_DownScaleOptical = ui_optionDialog.trackerspinbox->value();
	m_DownScaleDisparity = ui_optionDialog.depthspinbox->value();
	m_WinBlockSize = ui_optionDialog.blocksizepinbox->value();

	if (m_WinBlockSize < 3) m_WinBlockSize = 3;
	else if (m_WinBlockSize > 99) m_WinBlockSize = 99;
	else if ((m_WinBlockSize % 2) == 0) m_WinBlockSize++;

	
	if (m_DownScaleDisparity < 0.25f) 
		m_DownScaleDisparity = 0.25f;
	else if (m_DownScaleDisparity > 1.f)
		m_DownScaleDisparity = 1.f;
	
	if (m_DownScaleOptical < 0.25f) 
		m_DownScaleOptical = 0.25f;
	else if (m_DownScaleOptical > 1.f)
		m_DownScaleOptical = 1.f;
	
	m_OptTracker->setDownScale(m_DownScaleOptical);
	m_DMaker->setDownScale(m_DownScaleDisparity);
}

void PageScan::dialogReject() {
}

void PageScan::cameraOpenFail() {
	QMessageBox::warning(m_QMainWin, "Camera", "Fail to open camera.");
	back();
}
