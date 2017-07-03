#include "qmain.h"
#include "page01.h"
#include "page02.h"

proto01::proto01(QWidget *parent)
	: QMainWindow(parent) {

	move(QPoint(100, 100));

	ui_Page01 = nullptr;
	ui_Page02 = nullptr;
		
	openPage01();
}

proto01::~proto01()
{
	if (ui_Page01 != nullptr) delete ui_Page01;
	if (ui_Page02 != nullptr) delete ui_Page02;

	close();
}

void proto01::quitWindow() {
	close();
}

void proto01::openPage01() {
	if (ui_Page01 == nullptr) ui_Page01 = new Page01();
	ui_Page01->setUp(this);
}

void proto01::closePage01() {
	if (ui_Page01 != nullptr) {
		delete ui_Page01;
		ui_Page01 = nullptr;
	}
}

void proto01::openPage02() {
	if (ui_Page02 == nullptr) ui_Page02 = new Page02();
	ui_Page02->setUp(this);
}

void proto01::closePage02() {
	if (ui_Page02 != nullptr) {
		delete ui_Page02;
		ui_Page02 = nullptr;
	}
}
