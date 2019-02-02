#ifndef BASIC_MODE_H
#define BASIC_MODE_H

#include <QWidget>
#include "parser.h"

class Button;
class Display;
class TitleBar;
class NumButton;
class BackButton;
class QGridLayout;

class BasicMode : public QWidget
{
	Q_OBJECT

public:
	BasicMode(QWidget* parent = Q_NULLPTR);

private:
	Parser parser;

	const QChar MIN_SIGN{ 0x2212 };
	const QChar DIV_SIGN{ 0x00F7 };
	const QChar MUL_SIGN{ 0x00D7 };

	int bracketsRatio = 0;

	QGridLayout* layout;
	QGridLayout* buttons;
	TitleBar* titleBar;
	Display* display;
	Button* buttonLB;
	Button* buttonRB;
	Button* buttonC;
	BackButton* buttonBack;
	NumButton* button7;
	NumButton* button8;
	NumButton* button9;
	Button* buttonDIV;
	NumButton* button4;
	NumButton* button5;
	NumButton* button6;
	Button* buttonMUL;
	NumButton* button1;
	NumButton* button2;
	NumButton* button3;
	Button* buttonSUB;
	NumButton* button0;
	NumButton* buttonDOT;
	Button* buttonEQ;
	Button* buttonADD;

private slots:
	void dotClicked();
	void backClicked();
	void clearClicked();
	void digitClicked();
	void equalClicked();
	void operatorClicked();
	void leftBracketClicked();
	void rightBracketClicked();

	bool endsWithOperator();

	std::string fix(const std::string& str);
	std::string fixTail(const std::string& str);
	std::string fixLackOfMulSign(const std::string& str);
	std::string fixBracketsMismatch(const std::string& str);

	std::string getDisplayText();
	std::string getLastToken(const std::string& str);
	std::string getNumber(const std::string& str, size_t i);
	std::string getOperator(const std::string& str, size_t i);
};

#endif