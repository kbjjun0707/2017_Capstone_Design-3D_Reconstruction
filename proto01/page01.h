#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_page01.h"

class proto01;

class Page01 : public QObject {
	Q_OBJECT

public:
	Page01();
	~Page01();

	void setUp(proto01 *qMainWindow);

private:
	proto01		*qMainWin;
	Ui::page01	*ui;
	
	// Functions



	// Signals
	private slots:
	void quitWindow();
	void openPage02();
};

