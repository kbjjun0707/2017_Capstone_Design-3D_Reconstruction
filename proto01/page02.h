#pragma once

#include <QtWidgets/QMainWindow>
#include <QDir>
#include "ui_page02.h"
#include "ui_optiondialog.h"

#include <opencv2\opencv.hpp>
#include <thread>

#include "optical_.h"
#include "disparity.h"

class proto01;

class Page02 : public QObject {
	Q_OBJECT

public:
	Page02();
	~Page02();

	void setUp(proto01 *qMainWindow);
	void runCam();
	void runProc();

private:
	proto01		*qMainWin;
	Ui::page02	*ui;

	cv::VideoCapture	m_Cam;
	cv::Size			m_FrameUiSize;
	cv::Mat				m_CvFrame, m_CvStdImg, m_CvCmpImg, m_CvDisparityImg, m_CvReprojectImg;
	std::thread			m_CamThread;
	
	QDir				m_OptionFolder;
	QFile				m_OptionFile;
	QDialog				m_Dialog;
	Ui::Dialog			m_OptionDialog;

	iMiner::Tracker			m_OptTracker;
	iMiner::DisparityMaker	m_DisparityMkr;

	double				m_DownScaleOptical, m_DownScaleDisparity;
	int					m_WinBlockSize;

	bool				m_Capturing, m_GrabFrame, m_isPause, m_isProc, m_GrabProc, m_ViewCam, m_ViewColor;
	QPixmap				m_Frame, m_StdImg, m_CmpImg, m_DisparityImg, m_ReprojectImg;

	// Functions
	void convertCvMat2QPixmap(const cv::Mat &src, QPixmap &dst);
	void openCam(int idx = 0);
	void closeCam();
	void capture(int state = 0);
	
	// Signals
	private slots:
	void quitWindow();
	void backPage01();
	void startScan();
	void pause();
	void clearDatas();
	void optionCall();
	void chkVisiable();

	void dialogAccept();
	void dialogReject();
};


