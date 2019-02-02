#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>

namespace Ui
{
	class MainWindow;
}

class BasicMode;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = Q_NULLPTR);
	~MainWindow();

private:
	Ui::MainWindow* ui;

	BasicMode* basicMode;
};

#endif
