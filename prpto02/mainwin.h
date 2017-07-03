#ifndef MAINWIN_H
#define MAINWIN_H

#include <QtWidgets/QMainWindow>

class PageIntro;
class PageViewer;
class PageScan;

class MainWin : public QMainWindow
{
	Q_OBJECT

public:
	MainWin(QWidget *parent = 0);
	~MainWin();

private:
	
	PageIntro	*m_PageIntro;
	PageViewer	*m_PageViewer;
	PageScan	*m_PageScan;

	void init();
	void release();


public:
	void openPageIntro();
	void closePageIntro();

	void openPageViewer();
	void closePageViewer();

	void openPageScan();
	void closePageScan();

};

#endif // MAINWIN_H
