#include "qmain.h"
#include "page01.h"

Page01::Page01() {
	qMainWin = nullptr;
	ui = new Ui::page01();
}

Page01::~Page01() {
	qMainWin = nullptr;
	delete ui;
}

void Page01::setUp(proto01 * qMainWindow) {
	qMainWin = qMainWindow;
	ui->setupUi(qMainWindow);

	qMainWin->resize(400, 280);
	
	// menu event
	connect(ui->menu01quit, &QAction::triggered, this, &Page01::quitWindow);
	connect(ui->menu01scan, &QAction::triggered, this, &Page01::openPage02);

	ui->menu01viewer->setEnabled(false);		// 미구현 잠금
}

void Page01::openPage02() {
	qMainWin->openPage02();
	qMainWin->closePage01();
}

void Page01::quitWindow() {
	qMainWin->quitWindow();
}

