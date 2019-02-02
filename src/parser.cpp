#include <algorithm>
#include "parser.h"
#include "utils.h"
#include <cctype>

Parser::Vec Parser::to_postfix(const String& exp) const
{
	Vec stack, out;

	stack.reserve(exp.size());
	out.reserve(exp.size());

	for (size_t i = 0; i < exp.size(); ++i)
	{
		if (exp[i] == ' ')
			continue;
		else if (isdigit(exp[i]))
			convert_digit(out, exp, i);
		else if (isalpha(exp[i]))
			convert_function(stack, exp, i);
		else if (exp[i] == '(')
			convert_left_bracket(stack, exp, i);
		else if (exp[i] == ')')
			convert_right_bracket(stack, out);
		else if (exp[i] == ',')
			convert_separator(out, stack);
		else
			convert_operator(out, stack, exp, i);
	}
	while (stack.size())
	{
		if (is_bracket(stack.back())) throw brackets_mismatch{};
		move_last_elem(out, stack);
	}
	return out;
}

Parser::String Parser::calculate(const Vec& posix) const
{
	Vec s;
	s.reserve(posix.size());
	for (const auto& p : posix)
		isdigit(p[0]) ? parse_digit(s, p) : parse_operator(s, p);
	return get_result(s);
}

void Parser::set_precision(int precision)
{
	Real::set_default_prec(mpfr::digits2bits(precision));
	this->precision = precision;
}

bool Parser::is_binary_operator(const String& n) const
{
	Operator op;
	return get_operator(n, op) && op.type == Type::binary ? true : false;
}

bool Parser::is_unary_operator(const String& n) const
{
	Operator op;
	return get_operator(n, op) && op.type == Type::unary ? true : false;
}

bool Parser::is_constant(const String& n) const
{
	Operator op;
	return get_operator(n, op) && op.type == Type::constant ? true : false;
}

void Parser::convert_digit(Vec& o, const String& e, size_t& i) const
{
	push_token(o, e, i, [](auto c) { return isdigit(c) || c == '.'; });
}

void Parser::convert_function(Vec& s, const String& e, size_t& i) const
{
	push_token(s, e, i, [](auto c) { return isalpha(c); });
}

void Parser::convert_operator(Vec& o, Vec& s, const String& e, size_t i) const
{
	Operator op1, op2;
	String c(1, e[i]);

	get_operator(c, op1);

	if (c == "-" && (i == 0 || e[i - 1] == '(')) o.push_back("0");

	while (s.size() > 0 && (get_operator(s.back(), op2) ||
		isalpha(s.back()[0])))
	{
		if ((isalpha(s.back()[0]) ||
			op2.priority > op1.priority ||
			op2.priority == op1.priority &&
			op1.dir == Direction::left) &&
			s.back() != "(")
		{
			move_last_elem(o, s);
		}
		else break;
	}
	s.push_back(c);
}

void Parser::convert_left_bracket(Vec& s, const String& e, size_t& i) const
{
	s.push_back(String(1, e[i]));
}

void Parser::convert_right_bracket(Vec& s, Vec& o) const
{
	convert_brackets_content(s, o);
	s.pop_back();
}

void Parser::convert_separator(Vec& o, Vec& s) const
{
	convert_brackets_content(s, o);
}

void Parser::convert_brackets_content(Vec& s, Vec& o) const
{
	while (s.size() && s.back() != "(") move_last_elem(o, s);
	if (s.size() == 0) throw brackets_mismatch{};
}

void Parser::parse_digit(Vec& s, const String& d) const
{
	s.push_back(d);
}

void Parser::parse_operator(Vec& s, const String& d) const
{
	Operator op;
	Real result;

	if (!get_operator(d, op)) throw unknow_function{};

	switch (op.type)
	{
	case Type::constant: parse_constant(op, result); break;
	case Type::binary: parse_binary(s, op, result); break;
	case Type::unary: parse_unary(s, op, result); break;
	}

	s.push_back(result.toString());
}

void Parser::parse_constant(const Operator& op, Real& result) const
{
	result = std::get<Operator::Constant>(op.fun)();
}

void Parser::parse_binary(Vec& s, Operator& op, Real& result) const
{
	if (s.size() < 2) throw malformed_expression{};

	Real arg[2];

	for (auto& a : arg)
	{
		a = s.back();
		s.pop_back();
	}
	result = std::get<Operator::Binary>(op.fun)(arg[1], arg[0]);
}

void Parser::parse_unary(Vec& s, Operator& op, Real& result) const
{
	if (s.size() < 1) throw malformed_expression{};

	result = std::get<Operator::Unary>(op.fun)(s.back());
	s.pop_back();
}

bool Parser::get_operator(const String& name, Operator& op) const
{
	if (auto i = ops.find(name); i != ops.end())
	{
		op = i->second;
		return true;
	}
	return false;
}

Parser::String Parser::get_result(const Vec& s) const
{
	String result = (s.size()) ? s.back() : "";
	auto i = result.find('.') + 1;
	if (i != std::string::npos && i + precision < result.size())
		result = result.substr(0, i + precision);
	return result;
}