#ifndef PAGESCAN_H
#define PAGESCAN_H

#include "ui_pagescan.h"
#include "ui_optiondialog.h"

#include <qobject.h>
#include <qdir.h>
#include <qfile.h>
#include <qdialog.h>

#include <opencv2\opencv.hpp>

#include <thread>

class MainWin;

namespace jun {
	class Tracker;
	class DisparityMaker;
}


class PageScan : public QObject {
	Q_OBJECT

public:
	PageScan();
	~PageScan();

	void setUp(MainWin *qMainWindow);

	void videoRun(int idx);

private:
	MainWin			*m_QMainWin;
	Ui::ScanClass	ui;

	jun::Tracker		*m_OptTracker;
	jun::DisparityMaker	*m_DMaker;

	std::thread		m_CamThread;
	bool			m_IsCapturing, m_IsProc, m_GrabProc, m_SetStdFrame;
	
	QDir				m_OptionFolder;
	QFile				m_OptionFile;
	QDialog				optionDialog;
	Ui::Dialog			ui_optionDialog;

	cv::Mat m_Frame, m_ResizeFrame, m_StdFrame;
	cv::Mat m_CmpFrame, m_Disparity, m_Reproject;
	QPixmap m_QFrame, m_QStdFrame;

	double	m_DownScaleOptical, m_DownScaleDisparity;
	int		m_WinBlockSize;

	// Functions
	void convertMat2Pixmap(const cv::Mat & src, QPixmap & dst);
	void startCam(int idx = 0);
	void closeCam();
	void eventProc();


private slots:
	void quitWindow();
	void back();
	void startScan();
	void pause();
	void cleanUp();
	void saveFile();
	void openOptionDialog();
	void changeColor();
	void changeVB();
	void dialogAccept();
	void dialogReject();
	void cameraOpenFail();

Q_SIGNALS:
	void testtest();

};



#endif // !PAGESCAN_H

