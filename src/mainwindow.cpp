#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "basic_mode.h"

MainWindow::MainWindow(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

	basicMode = new BasicMode(this);
	setCentralWidget(basicMode);
}

MainWindow::~MainWindow()
{
	delete ui;
}
