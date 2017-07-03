#include "pageViewer.h"
#include "mainwin.h"
#include <qfiledialog.h>
#include <qmessagebox.h>

PageViewer::PageViewer() {
	m_QMainWin = nullptr;

	m_Min = 0.0f;
	m_Max = m_Max = 255.0f;
	m_PointSize = 1.f;
	m_ViewBoxVisiable = true;
}

PageViewer::~PageViewer() {
	m_QMainWin = nullptr;
}

void PageViewer::setUp(MainWin * qMainWindow) {
	m_QMainWin = qMainWindow;
	ui.setupUi(m_QMainWin);
	ui.lineEdit->clear();

	// menu event
	connect(ui.menuQuit, &QAction::triggered, this, &PageViewer::quitWindow);
	connect(ui.menuBack, &QAction::triggered, this, &PageViewer::back);
	connect(ui.menuColor, &QAction::triggered, this, &PageViewer::changeColor);
	connect(ui.menuOption, &QAction::triggered, this, &PageViewer::openOption);
	connect(ui.menuViewbox, &QAction::triggered, this, &PageViewer::chkViewBox);

	// ui event
	connect(ui.tbtn_dir, &QToolButton::clicked, this, &PageViewer::openFileDialog);
	connect(ui.btn_render, &QPushButton::clicked, this, &PageViewer::render);
}

void PageViewer::quitWindow() {
	m_QMainWin->close();
}

void PageViewer::back() {
	m_QMainWin->openPageIntro();
	m_QMainWin->closePageViewer();
}

void PageViewer::openFileDialog() {
	QString selfilter = tr("SCAN (*.scan)");
	QString FileName = QFileDialog::getOpenFileName(
		m_QMainWin,
		"load scan file",
		QDir::current().path(),
		"All files (*.*);;SCAN (*.scan)",
		&selfilter
	);
	ui.lineEdit->setText(FileName);
}

void PageViewer::render() {
	QString fileName = ui.lineEdit->text();

	if (fileName.size() > 0)
		ui.openGLWidget->render(fileName.toStdString().c_str());
}

void PageViewer::changeColor() {
	ui.openGLWidget->setColorVertexVisiable(ui.menuColor->isChecked());
}

void PageViewer::chkViewBox() {
	m_ViewBoxVisiable = ui.menuViewbox->isChecked();
	ui.openGLWidget->setViewBoxVisiable(m_ViewBoxVisiable);
}

void PageViewer::openOption() {
	ui_optionDialog.setupUi(&optionDialog);

	int diaX = (m_QMainWin->x() + (m_QMainWin->width() - optionDialog.width()) / 2);
	int diaY = (m_QMainWin->y() + (m_QMainWin->height() - optionDialog.height()) / 2);

	optionDialog.move(diaX, diaY);
	ui_optionDialog.minspinbox->setValue(m_Min);
	ui_optionDialog.maxspinbox->setValue(m_Max);
	ui_optionDialog.pointsizespinbox->setValue(m_PointSize);
	optionDialog.show();

	connect(ui_optionDialog.buttonBox, &QDialogButtonBox::accepted, this, &PageViewer::dialogAccept);
	connect(ui_optionDialog.buttonBox, &QDialogButtonBox::rejected, this, &PageViewer::dialogReject);
}

void PageViewer::dialogAccept() {
	m_Min = ui_optionDialog.minspinbox->value();
	m_Max = ui_optionDialog.maxspinbox->value();
	m_PointSize = ui_optionDialog.pointsizespinbox->value();

	ui.openGLWidget->setZScale(m_PointSize, m_Min, m_Max);
}

void PageViewer::dialogReject() {
}
