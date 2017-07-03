#ifndef PAGEINTRO_H
#define PAGEINTRO_H

#include "ui_pageintro.h"

#include <qobject.h>

class MainWin;

class PageIntro : public QObject {
	Q_OBJECT

public:
	PageIntro();
	~PageIntro();

	void setUp(MainWin *qMainWindow);

private:
	MainWin *m_QMainWin;
	Ui::IntroClass ui;


	// Functions



	// Signals
private slots:
	void quitWindow();
	void startViewer();
	void startScan();
};



#endif // !PAGEINTRO_H

