#include "mainwin.h"
#include "pageIntro.h"
#include "pageViewer.h"
#include "pageScan.h"


MainWin::MainWin(QWidget *parent)
	: QMainWindow(parent) {

	init();
	openPageIntro();

}

MainWin::~MainWin() {
	release();
}

void MainWin::init() {
	m_PageIntro = nullptr;
	m_PageViewer = nullptr;
	m_PageScan = nullptr;
}

void MainWin::openPageIntro() {
	if (m_PageIntro == nullptr)
		m_PageIntro = new PageIntro();
	m_PageIntro->setUp(this);
}

void MainWin::closePageIntro() {
	if (m_PageIntro)
		delete m_PageIntro;
	m_PageIntro = nullptr;
}

void MainWin::openPageViewer() {
	if (m_PageViewer == nullptr)
		m_PageViewer = new PageViewer();
	m_PageViewer->setUp(this);

}

void MainWin::closePageViewer() {
	if (m_PageViewer)
		delete m_PageViewer;
	m_PageViewer = nullptr;
}

void MainWin::openPageScan() {
	if (m_PageScan == nullptr)
		m_PageScan = new PageScan();
	m_PageScan->setUp(this);
}

void MainWin::closePageScan() {
	if (m_PageScan) 
		delete m_PageScan;
	m_PageScan = nullptr;
}

void MainWin::release() {
	closePageScan();
	closePageViewer();
	closePageIntro();
}
