#include <QHBoxLayout>
#include <QMouseEvent>
#include "titlebar.h"
#include "buttons.h"

TitleBar::TitleBar(QWidget* parent) : QWidget(parent), parent(parent)
{
	layout = new QHBoxLayout();
	close = new CloseButton();
	minimize = new MinimizeButton();

	layout->addWidget(minimize);
	layout->addWidget(close);
	layout->setAlignment(Qt::AlignRight | Qt::AlignTop);
	layout->setContentsMargins(1, 1, 1, 0);
	layout->setSpacing(0);

	setFixedHeight(50);
	setLayout(layout);

	connect(close, SIGNAL(clicked()), parent, SLOT(close()));
	connect(close, SIGNAL(pressed()), this, SLOT(closePressed()));
	connect(close, SIGNAL(released()), this, SLOT(closeReleased()));
	connect(minimize, SIGNAL(clicked()), parent, SLOT(showMinimized()));
	connect(minimize, SIGNAL(pressed()), this, SLOT(minimizePressed()));
	connect(minimize, SIGNAL(released()), this, SLOT(minimizeReleased()));
}

void TitleBar::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && parent)
	{
		cursor = event->globalPos() - parent->geometry().topLeft();
		event->accept();
	}
}

void TitleBar::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton && parent)
	{
		parent->move(event->globalPos() - cursor);
		event->accept();
	}
}

void TitleBar::closePressed()
{
	close->setIcon(QIcon(":/icons/close_pressed.png"));
}

void TitleBar::closeReleased()
{
	close->setIcon(QIcon(":/icons/close_hover.png"));
}

void TitleBar::minimizePressed()
{
	minimize->setIcon(QIcon(":/icons/minimize_pressed.png"));
}

void TitleBar::minimizeReleased()
{
	minimize->setIcon(QIcon(":/icons/minimize_hover.png"));
}