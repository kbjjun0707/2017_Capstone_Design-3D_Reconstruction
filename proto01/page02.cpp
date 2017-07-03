#include "qmain.h"
#include "page02.h"

#include <QMessagebox>
#include <qdebug.h>

Page02::Page02() {
	qMainWin = nullptr;
	ui = new Ui::page02();

	m_Capturing = false;
	m_GrabFrame = false;
	m_isPause = false;
	m_isProc = false;
	m_GrabProc = false;
	
	m_OptionFolder.setPath(m_OptionFolder.currentPath() + "/option");
	m_OptionFile.setFileName(m_OptionFolder.path() + "/options.txt");

	if (!m_OptionFolder.exists())
		m_OptionFolder.mkpath(m_OptionFolder.path());
	if (m_OptionFile.exists()) {
		m_OptionFile.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream in(&m_OptionFile);
		in >> m_DownScaleOptical >> m_DownScaleDisparity >> m_WinBlockSize;
	} else {
		m_OptionFile.open(QIODevice::WriteOnly | QIODevice::Text);
		QTextStream out(&m_OptionFile);
		out << "0.25 0.4 5" << endl;
		m_DownScaleOptical = 0.25;
		m_DownScaleDisparity = 0.4;
		m_WinBlockSize = 5;
	}
	m_OptionFile.close();
}

Page02::~Page02() {
	closeCam();
	m_OptionFile.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&m_OptionFile);
	out << m_DownScaleOptical << " " << m_DownScaleDisparity << " " << m_WinBlockSize << endl;
	m_OptionFile.close();

	qMainWin = nullptr;
	delete ui;
}

void Page02::setUp(proto01 * qMainWindow) {
	qMainWin = qMainWindow;
	ui->setupUi(qMainWin);

	m_FrameUiSize.width = ui->lb_cam->width();
	m_FrameUiSize.height = ui->lb_cam->height();
	m_ViewCam = ui->menu02cammodel->isChecked();
	m_ViewColor = ui->menu02color->isChecked();

	ui->openGLWidget->setInit(&m_OptTracker, &m_DisparityMkr);
	ui->openGLWidget->setCamView(m_ViewCam);
	ui->openGLWidget->setColorVertexVisiable(m_ViewColor);
	
	ui->btn_clear->setEnabled(false);
	ui->btn_save->setEnabled(false);
	ui->btn_stop->setEnabled(false);

	openCam();
	m_OptTracker.setDownScale(m_DownScaleOptical);
	m_DisparityMkr.setDownScale(m_DownScaleDisparity);

	// menu event
	connect(ui->menu02back, &QAction::triggered, this, &Page02::backPage01);
	connect(ui->menu02quit, &QAction::triggered, this, &Page02::quitWindow);
	connect(ui->menu02option, &QAction::triggered, this, &Page02::optionCall);
	connect(ui->menu02cammodel, &QAction::triggered, this, &Page02::chkVisiable);
	connect(ui->menu02color, &QAction::triggered, this, &Page02::chkVisiable);

	// ui event
	connect(ui->btn_start, &QPushButton::clicked, this, &Page02::startScan);
	connect(ui->btn_clear, &QPushButton::clicked, this, &Page02::clearDatas);
	connect(ui->btn_stop, &QPushButton::clicked, this, &Page02::pause);
}

void Page02::runCam() {
	while (m_Capturing) {
		m_Cam >> m_CvFrame;
		convertCvMat2QPixmap(m_CvFrame, m_Frame);
		ui->lb_cam->setPixmap(m_Frame);

		if (m_isProc) {
			m_GrabProc = true;
			runProc();
			m_GrabProc = false;
		}
		cv::waitKey(40);
	}
}

void Page02::runProc() {
	if (m_Capturing) {
		m_OptTracker.processImage(m_CvFrame);
		m_OptTracker.warpAffine(m_CvFrame, m_CvCmpImg);
		double disparity = m_OptTracker.getDisparity();
		if (disparity > 0) {
			m_DisparityMkr.setting(63, m_WinBlockSize, disparity, 0, 3, 7000, 1.25);
			m_DisparityMkr.compute(m_CvStdImg, m_CvCmpImg);
		} else if (disparity < 0) {
			m_DisparityMkr.setting(63, m_WinBlockSize, -disparity, 0, 3, 7000, 1.25);
			m_DisparityMkr.compute(m_CvCmpImg, m_CvStdImg);
		}
		else {
			return;
		}
		m_CvDisparityImg = m_DisparityMkr.getVisFiltedDisparity();
		m_CvReprojectImg = m_DisparityMkr.getReprojectMat();
		convertCvMat2QPixmap(m_CvCmpImg, m_CmpImg);
		convertCvMat2QPixmap(m_CvDisparityImg, m_DisparityImg);
		convertCvMat2QPixmap(m_DisparityMkr.getVisReprojectMat(), m_ReprojectImg);

		ui->lb_cmp->setPixmap(m_CmpImg);
		ui->lb_disparity->setPixmap(m_DisparityImg);
		ui->lb_reproject->setPixmap(m_ReprojectImg);
	}
}

void Page02::quitWindow() {
	qMainWin->quitWindow();
}

void Page02::convertCvMat2QPixmap(const cv::Mat & src, QPixmap & dst) {
	cv::Mat cvtmp;
	QImage tmp;

	cv::resize(src, cvtmp, m_FrameUiSize);

	if (cvtmp.channels() == 3) {
		cv::cvtColor(cvtmp, cvtmp, cv::COLOR_BGR2RGB);
		tmp = QImage(cvtmp.data, cvtmp.cols, cvtmp.rows, QImage::Format::Format_RGB888);
		
	} else if (cvtmp.channels() == 1) {
		tmp = QImage(cvtmp.data, cvtmp.cols, cvtmp.rows, QImage::Format::Format_Grayscale8);
	}

	dst = QPixmap::fromImage(tmp).copy();
}

void Page02::openCam(int idx) {
	closeCam();

	if (!m_Cam.open(idx)) {
		QMessageBox::warning(qMainWin, "3D Scanner", "카메라를 여는데 실패하였습니다.");
		return;
	}
	m_Capturing = true;
	m_CamThread = std::thread([&]() {
		runCam();
	});
}

void Page02::closeCam() {
	m_Capturing = false;
	if (m_CamThread.joinable()) m_CamThread.join();
	if (m_Cam.isOpened()) m_Cam.release();
}

void Page02::capture(int state) {
	if (m_Capturing) {
		//m_GrabFrame = true;
		m_CvStdImg = m_CvFrame.clone();
		m_OptTracker.setStdImg(m_CvStdImg);
		convertCvMat2QPixmap(m_CvStdImg, m_StdImg);
		ui->lb_std->setPixmap(m_StdImg);
		//m_GrabFrame = false;
	}
}

void Page02::backPage01() {
	qMainWin->openPage01();
	qMainWin->closePage02();
}

void Page02::startScan() {
	clearDatas();

	m_isPause = false;
	ui->btn_stop->setText("pause");
	ui->btn_clear->setEnabled(true);
	ui->btn_save->setEnabled (true);
	ui->btn_stop->setEnabled (true);

	m_OptTracker.setDownScale(m_DownScaleOptical);
	m_DisparityMkr.setDownScale(m_DownScaleDisparity);
	capture();
	m_isProc = true;
}

void Page02::pause() {
	m_isPause = !m_isPause;

	if (m_isPause) {
		ui->btn_start->setEnabled(false);
		ui->btn_stop->setText("reStart");
		m_isProc = false;
	} else {
		ui->btn_start->setEnabled(true);
		ui->btn_stop->setText("pause");
		m_isProc = true;
	}
}

void Page02::clearDatas() {
	m_isPause = false;
	m_isProc = false;

	ui->btn_stop->setText("pause");
	ui->btn_clear->setEnabled(false);
	ui->btn_save->setEnabled(false);
	ui->btn_stop->setEnabled(false);
	ui->btn_start->setEnabled(true);

	while (m_GrabProc);

	ui->lb_std->setPixmap(QPixmap(0, 0));
	ui->lb_cmp->setPixmap(QPixmap(0, 0));
	ui->lb_disparity->setPixmap(QPixmap(0, 0));
	ui->lb_reproject->setPixmap(QPixmap(0, 0));
}

void Page02::optionCall() {
	m_OptionDialog.setupUi(&m_Dialog);
	int diaX = ((qMainWin->x() + qMainWin->width() - m_Dialog.width()/2) / 2);
	int diaY = ((qMainWin->y() + qMainWin->height() - m_Dialog.height()/2) / 2);
	m_Dialog.move(diaX, diaY);
	m_OptionDialog.trackerspinbox->setValue(m_DownScaleOptical);
	m_OptionDialog.depthspinbox->setValue(m_DownScaleDisparity);
	m_OptionDialog.blocksizepinbox->setValue(m_WinBlockSize);
	connect(m_OptionDialog.buttonBox, &QDialogButtonBox::accepted, this, &Page02::dialogAccept);
	connect(m_OptionDialog.buttonBox, &QDialogButtonBox::rejected, this, &Page02::dialogReject);
	m_Dialog.show();
}

void Page02::chkVisiable() {
	m_ViewCam = ui->menu02cammodel->isChecked();
	m_ViewColor = ui->menu02color->isChecked();

	ui->openGLWidget->setCamView(m_ViewCam);
	ui->openGLWidget->setColorVertexVisiable(m_ViewColor);
}

void Page02::dialogAccept() {
	m_DownScaleOptical		= m_OptionDialog.trackerspinbox->value();
	m_DownScaleDisparity	= m_OptionDialog.depthspinbox->value();
	m_WinBlockSize			= m_OptionDialog.blocksizepinbox->value();
}

void Page02::dialogReject() {

}
