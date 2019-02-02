#include "basic_mode.h"
#include <QGridLayout>
#include "titlebar.h"
#include "display.h"
#include "buttons.h"
#include "qcalc.h"
#include <cctype>
#include <cmath>

BasicMode::BasicMode(QWidget* parent) : QWidget(parent)
{
	add_operators(parser);

	layout = new QGridLayout(this);
	buttons = new QGridLayout();
	titleBar = new TitleBar(parent);
	display = new Display();

	buttonLB = new Button("(");
	buttonRB = new Button(")");
	buttonC = new Button("C");
	buttonBack = new BackButton();

	button7 = new NumButton("7");
	button8 = new NumButton("8");
	button9 = new NumButton("9");
	buttonDIV = new Button(DIV_SIGN);

	button4 = new NumButton("4");
	button5 = new NumButton("5");
	button6 = new NumButton("6");
	buttonMUL = new Button(MUL_SIGN);

	button1 = new NumButton("1");
	button2 = new NumButton("2");
	button3 = new NumButton("3");
	buttonSUB = new Button(MIN_SIGN);

	button0 = new NumButton("0");
	buttonDOT = new NumButton(".");
	buttonEQ = new Button("=");
	buttonADD = new Button("+");

	layout->addWidget(titleBar, 0, 0, 1, 4);
	layout->addWidget(display, 1, 0, 1, 4);

	buttons->addWidget(buttonLB, 0, 0);
	buttons->addWidget(buttonRB, 0, 1);
	buttons->addWidget(buttonC, 0, 2);
	buttons->addWidget(buttonBack, 0, 3);

	buttons->addWidget(button7, 1, 0);
	buttons->addWidget(button8, 1, 1);
	buttons->addWidget(button9, 1, 2);
	buttons->addWidget(buttonDIV, 1, 3);

	buttons->addWidget(button4, 2, 0);
	buttons->addWidget(button5, 2, 1);
	buttons->addWidget(button6, 2, 2);
	buttons->addWidget(buttonMUL, 2, 3);

	buttons->addWidget(button1, 3, 0);
	buttons->addWidget(button2, 3, 1);
	buttons->addWidget(button3, 3, 2);
	buttons->addWidget(buttonSUB, 3, 3);

	buttons->addWidget(button0, 4, 0);
	buttons->addWidget(buttonDOT, 4, 1);
	buttons->addWidget(buttonEQ, 4, 2);
	buttons->addWidget(buttonADD, 4, 3);

	buttons->setContentsMargins(20, 10, 20, 20);
	buttons->setSpacing(10);

	layout->setMargin(0);
	layout->setSpacing(0);
	layout->setAlignment(Qt::AlignTop);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->addLayout(buttons, 3, 0);

	buttonLB->setObjectName("bracket");
	buttonRB->setObjectName("bracket");
	buttonEQ->setObjectName("equal");

	connect(button0, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button1, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button2, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button3, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button4, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button5, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button6, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button7, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button8, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(button9, SIGNAL(clicked()), this, SLOT(digitClicked()));
	connect(buttonC, SIGNAL(clicked()), this, SLOT(clearClicked()));
	connect(buttonDOT, SIGNAL(clicked()), this, SLOT(dotClicked()));
	connect(buttonEQ, SIGNAL(clicked()), this, SLOT(equalClicked()));
	connect(buttonBack, SIGNAL(clicked()), this, SLOT(backClicked()));
	connect(buttonDIV, SIGNAL(clicked()), this, SLOT(operatorClicked()));
	connect(buttonMUL, SIGNAL(clicked()), this, SLOT(operatorClicked()));
	connect(buttonSUB, SIGNAL(clicked()), this, SLOT(operatorClicked()));
	connect(buttonADD, SIGNAL(clicked()), this, SLOT(operatorClicked()));
	connect(buttonLB, SIGNAL(clicked()), this, SLOT(leftBracketClicked()));
	connect(buttonRB, SIGNAL(clicked()), this, SLOT(rightBracketClicked()));
}

void BasicMode::dotClicked()
{
	std::string text = getDisplayText();
	size_t i = text.length();

	if (i && isdigit(text[--i]))
	{
		while (i && isdigit(text[i])) --i;
		if (text[i] != '.') display->append(".");
	}
}

void BasicMode::backClicked()
{
	QString text = display->text();

	if (text.length())
	{
		if (text[text.length() - 1] == '(') ++bracketsRatio;
		else if (text[text.length() - 1] == ')') --bracketsRatio;

		display->backspace();
	}
}

void BasicMode::clearClicked()
{
	display->clear();
	bracketsRatio = 0;
}

void BasicMode::digitClicked()
{
	QPushButton* button = (QPushButton*)sender();
	display->append(button->text());
}

void BasicMode::equalClicked()
{
	try
	{
		std::string str = fix(getDisplayText());
		std::string result = parser.calculate(parser.to_postfix(str));
		display->setText(result.c_str());
	}
	catch (std::exception& e)
	{
		display->setMessage(e.what());
	}
	catch (...)
	{
		display->setMessage("Error");
	}
}

void BasicMode::operatorClicked()
{
	if (QPushButton* button = (QPushButton*)sender();
		!endsWithOperator() || !display->text().length() &&
		button->text() == MIN_SIGN)
	{
		display->append(button->text());
	}
}

void BasicMode::leftBracketClicked()
{
	QString text = display->text();
	if (text.length() == 0 || text[text.length() - 1] != '.')
	{
		display->append("(");
		--bracketsRatio;
	}
}

void BasicMode::rightBracketClicked()
{
	if (bracketsRatio)
	{
		display->append(")");
		++bracketsRatio;
	}
}

std::string BasicMode::fix(const std::string& str)
{
	return fixBracketsMismatch(fixLackOfMulSign(fixTail(str)));
}

std::string BasicMode::fixTail(const std::string& str)
{
	std::string s = str;

	for (std::string token = getLastToken(s);
		parser.is_binary_operator(token) ||
		parser.is_unary_operator(token) ||
		token == "(" || token == ".";
		token = getLastToken(s))
	{
		if (token == "(") ++bracketsRatio;
		s.erase(s.length() - token.length());
	}

	return s;
}

std::string BasicMode::fixLackOfMulSign(const std::string& str)
{
	std::string s = str;

	size_t i = s.find('(');

	for (; i != std::string::npos; i = s.find('(', i + 2))
	{
		if (!i) continue;
		auto op = getOperator(s, i - 1);
		if (isdigit(s[i - 1]) || parser.is_constant(op))
			s.insert(i, "*");
	}

	return s;
}

std::string BasicMode::fixBracketsMismatch(const std::string& str)
{
	std::string s = str;

	s.insert(s.length(), std::abs(bracketsRatio), ')');

	return s;
}

std::string BasicMode::getDisplayText()
{
	QString text = display->text();
	text.replace(MIN_SIGN, "-");
	text.replace(MUL_SIGN, "*");
	text.replace(DIV_SIGN, "/");
	return text.toStdString();
}

std::string BasicMode::getLastToken(const std::string& str)
{
	size_t i = str.length();

	if (!i) return "";
	else if (isdigit(str.back())) return getNumber(str, i);
	else if (str.back() == '.') return ".";
	else if (str.back() == '(') return "(";
	else if (str.back() == ')') return ")";
	else return getOperator(str, i);
}

std::string BasicMode::getNumber(const std::string& str, size_t i)
{
	std::string token;

	while (i-- && (isdigit(str[i]) || str[i] == '.')) token += str[i];

	return token;
}

std::string BasicMode::getOperator(const std::string& str, size_t i)
{
	std::string token;

	while (i-- && !isdigit(str[i]) &&
		str[i] != '(' && str[i] != ')' && str[i] != '.')
	{
		token += str[i];
	}

	return token;
}

bool BasicMode::endsWithOperator()
{
	std::string token = getLastToken(getDisplayText());

	return !display->text().length() || token == "." ||
		parser.is_binary_operator(token) ||
		parser.is_unary_operator(token);
}