#ifndef FILTERS_H
#define FILTERS_H

#include <QObject>

class QEvent;

class ButtonModeFilter : public QObject
{
	Q_OBJECT
public:
	explicit ButtonModeFilter(QObject* parent = Q_NULLPTR);
	virtual bool eventFilter(QObject* watched, QEvent* event);
};

class ButtonCloseFilter : public QObject
{
	Q_OBJECT
public:
	explicit ButtonCloseFilter(QObject* parent = Q_NULLPTR);
	virtual bool eventFilter(QObject* watched, QEvent* event);
};

class ButtonMinimizeFilter : public QObject
{
	Q_OBJECT
public:
	explicit ButtonMinimizeFilter(QObject* parent = Q_NULLPTR);
	virtual bool eventFilter(QObject* watched, QEvent* event);
};

class ButtonBackFilter : public QObject
{
	Q_OBJECT
public:
	explicit ButtonBackFilter(QObject* parent = Q_NULLPTR);
	virtual bool eventFilter(QObject* watched, QEvent* event);
};

#endif
