#include <QPushButton>
#include "filters.h"
#include <QEvent>

namespace
{
	bool doEvent(QObject* watched, QEvent* event,
		const char* unhover, const char* hover);
}

ButtonModeFilter::ButtonModeFilter(QObject* parent) : QObject(parent) {}

bool ButtonModeFilter::eventFilter(QObject* watched, QEvent* event)
{
	return doEvent(watched, event, ":/icons/mode.png",
		":/icons/mode_hover.png");
}

ButtonCloseFilter::ButtonCloseFilter(QObject* parent) : QObject(parent) {}

bool ButtonCloseFilter::eventFilter(QObject* watched, QEvent* event)
{
	return doEvent(watched, event, ":/icons/close.png",
		":/icons/close_hover.png");
}

ButtonMinimizeFilter::ButtonMinimizeFilter(QObject* parent) : QObject(parent) {}

bool ButtonMinimizeFilter::eventFilter(QObject* watched, QEvent* event)
{
	return doEvent(watched, event, ":/icons/minimize.png",
		":/icons/minimize_hover.png");
}

ButtonBackFilter::ButtonBackFilter(QObject* parent) : QObject(parent) {}

bool ButtonBackFilter::eventFilter(QObject* watched, QEvent* event)
{
	return doEvent(watched, event, ":/icons/back.png",
		":/icons/back_hover.png");
}

namespace
{
	bool doEvent(QObject* watched, QEvent* event,
		const char* unhover, const char* hover)
	{
		QPushButton* button = qobject_cast<QPushButton*>(watched);
		if (!button) return false;

		if (event->type() == QEvent::Enter)
		{
			button->setIcon(QIcon(hover));
			return true;
		}

		if (event->type() == QEvent::Leave)
		{
			button->setIcon(QIcon(unhover));
			return true;
		}

		return false;
	}
}
