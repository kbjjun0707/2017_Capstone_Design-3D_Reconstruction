#include "pageIntro.h"

#include "mainwin.h"


PageIntro::PageIntro() {
	m_QMainWin = nullptr;
}

PageIntro::~PageIntro() {
	m_QMainWin = nullptr;
}

void PageIntro::setUp(MainWin * qMainWindow) {
	m_QMainWin = qMainWindow;
	ui.setupUi(m_QMainWin);
	m_QMainWin->resize(0, 0);

	ui.mainlabel->setPixmap(QPixmap("Resources/3D scanner.png"));

	// ui event
	connect(ui.btn_Viewer, &QPushButton::clicked, this, &PageIntro::startViewer);
	connect(ui.btn_Startscan, &QPushButton::clicked, this, &PageIntro::startScan);

	// menu event
	connect(ui.menuQuit, &QAction::triggered, this, &PageIntro::quitWindow);
	connect(ui.menuViewer, &QAction::triggered, this, &PageIntro::startViewer);
	connect(ui.menuScanner, &QAction::triggered, this, &PageIntro::startScan);
}

void PageIntro::quitWindow() {
	m_QMainWin->close();
}

void PageIntro::startViewer() {
	m_QMainWin->openPageViewer();
	m_QMainWin->closePageIntro();
}

void PageIntro::startScan() {
	m_QMainWin->openPageScan();
	m_QMainWin->closePageIntro();
}

