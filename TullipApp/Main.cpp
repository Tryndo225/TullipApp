#include "DateTime.h"
#include <QApplication>
#include "DataBaseGUI.h"

int main(int argc, char* argv[])
{
	QApplication application(argc, argv);

	DataBaseGUI mainWindow;
	mainWindow.show();

	return application.exec();
}