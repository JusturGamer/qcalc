#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>

class Button : public QPushButton
{
	Q_OBJECT
public:
	Button(QWidget* parent = Q_NULLPTR);
	Button(const QString& text, QWidget* parent = Q_NULLPTR);
};

class NumButton : public Button
{
	Q_OBJECT
public:
	NumButton(const QString& text, QWidget* parent = Q_NULLPTR);
};

class BackButton : public Button
{
	Q_OBJECT
public:
	BackButton(QWidget* parent = Q_NULLPTR);
};

class CloseButton : public QPushButton
{
	Q_OBJECT
public:
	CloseButton(QWidget* parent = Q_NULLPTR);
};

class MinimizeButton : public QPushButton
{
	Q_OBJECT
public:
	MinimizeButton(QWidget* parent = Q_NULLPTR);
};

#endif
