#include <QApplication>
#include "mainwindow.h"
#include <QFile>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/icons/icon.ico"));
	QFile file(":/style.qss");
	file.open(QFile::ReadOnly);
	QString style = QLatin1String(file.readAll());
	app.setStyleSheet(style);
	MainWindow window;
	window.show();
	return app.exec();
}
