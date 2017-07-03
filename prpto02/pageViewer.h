#ifndef PAGEVIEWER_H
#define PAGEVIEWER_H

#include "ui_pageviewer.h"
#include "ui_distancedialog.h"

#include <qdialog.h>
#include <qobject.h>

class MainWin;

class PageViewer : public QObject {
	Q_OBJECT

public:
	PageViewer();
	~PageViewer();

	void setUp(MainWin *qMainWindow);

private:
	MainWin *m_QMainWin;
	Ui::ViewerClass ui;

	QDialog				optionDialog;
	Ui::Dialog2			ui_optionDialog;

	float	m_Min, m_Max, m_PointSize;
	bool	m_ViewBoxVisiable;

private slots :
	void quitWindow();
	void back();
	void openFileDialog();
	void render();
	void changeColor();
	void chkViewBox();

	void openOption();
	void dialogAccept();
	void dialogReject();
};



#endif // !PAGEVIEWER_H

