#ifndef DISPLAY_H
#define DISPLAY_H

#include <QLineEdit>
#include <QWidget>
#include <QLabel>

class QLabel;
class QScrollArea;
class QGridLayout;

class Display : public QWidget
{
	Q_OBJECT

public:
	Display(QWidget* parent = Q_NULLPTR);

	void clear() { lineEdit->clear(); }
	void clearMessage() { label->clear(); }
	QString text() { return lineEdit->text(); }
	void backspace() { lineEdit->backspace(); }
	void append(const QString& text) { lineEdit->insert(text); }
	void setText(const QString& text) { lineEdit->setText(text); }
	void setMessage(const QString& text) { label->setText(text); }

private:
	QLabel* label;
	QGridLayout* layout;
	QLineEdit* lineEdit;
	QScrollArea* scrollArea;

private slots:
	void resizeToContent();
};

#endif
