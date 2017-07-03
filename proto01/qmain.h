#ifndef QMAIN_H
#define QMAIN_H

#include <QtWidgets/QMainWindow>
#include <opencvLibs.h>

class Page01;
class Page02;

class proto01 : public QMainWindow {
	Q_OBJECT

private:
	Page01	*ui_Page01;
	Page02	*ui_Page02;

public:
	proto01(QWidget *parent = 0);
	~proto01();

	// Functions
	void quitWindow();
	void openPage01();
	void closePage01();
	void openPage02();
	void closePage02();

};

#endif // QMAIN_H
