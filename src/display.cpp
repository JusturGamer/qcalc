#include <QFontMetrics>
#include <QStyleOption>
#include <QScrollArea>
#include <QGridLayout>
#include <QScrollBar>
#include <QPainter>
#include "display.h"

Display::Display(QWidget* parent) : QWidget(parent)
{
	label = new QLabel();
	layout = new QGridLayout();
	lineEdit = new QLineEdit();
	scrollArea = new QScrollArea();

	lineEdit->setReadOnly(true);
	lineEdit->setFixedHeight(70);
	lineEdit->setPlaceholderText("0");
	lineEdit->setAlignment(Qt::AlignTop | Qt::AlignRight);

	label->setFixedHeight(18);
	label->setObjectName("message");

	scrollArea->setWidget(lineEdit);
	scrollArea->setWidgetResizable(true);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	layout->setContentsMargins(20, 0, 20, 0);
	layout->addWidget(scrollArea, 0, 0);
	layout->addWidget(label, 0, 0);

	setLayout(layout);
	setFixedHeight(70);

	connect(lineEdit, SIGNAL(textChanged(QString)), this,
		SLOT(resizeToContent()));
}

void Display::resizeToContent()
{
	QFontMetrics fm(lineEdit->fontMetrics());

	int extraSpace = 28;
	int borderWidth = 1;
	int textWidth = fm.width(lineEdit->text()) + extraSpace;
	int displayWidth = scrollArea->width() - 2 * borderWidth;

	if (textWidth >= displayWidth) lineEdit->setFixedWidth(textWidth);
	else lineEdit->setFixedWidth(displayWidth);

	scrollArea->horizontalScrollBar()->setSliderPosition(lineEdit->width());
	clearMessage();
}