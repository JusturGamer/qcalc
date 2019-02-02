#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

class QHBoxLayout;
class CloseButton;
class MinimizeButton;

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	TitleBar(QWidget* parent = Q_NULLPTR);

private:
	QPoint cursor;
	QWidget* parent;
	QHBoxLayout* layout;
	CloseButton* close;
	MinimizeButton* minimize;

protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);

private slots:
	void closePressed();
	void closeReleased();
	void minimizePressed();
	void minimizeReleased();
};

#endif
