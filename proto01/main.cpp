#include "qmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	proto01 w;
	w.show();

	return a.exec();
}