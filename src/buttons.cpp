#include "buttons.h"
#include "filters.h"

namespace
{
	void initButton(Button* button);
	void initTitleBarButton(QPushButton* button, const char* icon);
}

Button::Button(QWidget* parent) : QPushButton(parent)
{
	initButton(this);
}

Button::Button(const QString& text, QWidget* parent) : QPushButton(text, parent)
{
	initButton(this);
}

NumButton::NumButton(const QString& text, QWidget* parent)
	: Button(text, parent)
{
	setObjectName("buttonNUM");
}

BackButton::BackButton(QWidget* parent) : Button(parent)
{
	setIcon(QIcon(":/icons/back.png"));
	setIconSize(QSize(22, 22));

	ButtonBackFilter* backFilter = new ButtonBackFilter(this);
	installEventFilter(backFilter);
}

ModeButton::ModeButton(QWidget* parent) : QPushButton(parent)
{
	initTitleBarButton(this, ":/icons/mode.png");
	setObjectName("mode");

	ButtonModeFilter* modeFilter = new ButtonModeFilter(this);
	installEventFilter(modeFilter);
}

CloseButton::CloseButton(QWidget* parent) : QPushButton(parent)
{
	initTitleBarButton(this, ":/icons/close.png");
	setObjectName("close");

	ButtonCloseFilter* closeFilter = new ButtonCloseFilter(this);
	installEventFilter(closeFilter);
}

MinimizeButton::MinimizeButton(QWidget* parent) : QPushButton(parent)
{
	initTitleBarButton(this, ":/icons/minimize.png");
	setObjectName("minimize");

	ButtonMinimizeFilter* minimizeFilter = new ButtonMinimizeFilter(this);
	installEventFilter(minimizeFilter);
}

namespace
{
	void initButton(Button* button)
	{
		button->setFixedSize(80, 40);
		button->setFlat(true);
	}

	void initTitleBarButton(QPushButton* button, const char* icon)
	{
		button->setIcon(QIcon(icon));
		button->setIconSize(QSize(16, 16));
		button->setFixedSize(50, 34);
		button->setFlat(true);
	}
}
