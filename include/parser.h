#ifndef PARSER_H
#define PARSER_H

#define _MPFR_NO_DEPRECATED_ROOT
#define _MPFR_NO_DEPRECATED_GRANDOM

#include <unordered_map>
#include <functional>
#include <exception>
#include "mpreal.h"
#include <variant>
#include <vector>
#include <string>
#include <map>

class Parser
{
	typedef std::vector<std::string> Vec;
	typedef std::string String;
	typedef mpfr::mpreal Real;

public:
	enum class Direction { left, right };
	enum class Type { binary, unary, constant };

	template<typename T>
	void add_operator(String n, int p, Direction d, T f);

	Vec to_postfix(const String& exp) const;
	String calculate(const Vec& posix) const;
	void set_precision(int precision);
	bool is_binary_operator(const String& n) const;
	bool is_unary_operator(const String& n) const;
	bool is_constant(const String& n) const;

private:
	struct Operator
	{
		typedef std::function<Real(Real, Real)> Binary;
		typedef std::function<Real(Real)> Unary;
		typedef std::function<Real()> Constant;

		Operator() = default;

		Operator(int p, Direction d, Unary f)
			: priority(p), dir(d), type(Type::unary), fun(f) {}

		Operator(int p, Direction d, Binary f)
			: priority(p), dir(d), type(Type::binary), fun(f) {}

		Operator(int p, Direction d, Constant f)
			: priority(p), dir(d), type(Type::constant), fun(f) {}

		int priority;
		Direction dir;
		Type type;
		std::variant<Binary, Unary, Constant> fun;
	};

	std::unordered_map<String, Operator> ops;
	int precision = std::numeric_limits<Real>::digits();

	void convert_digit(Vec& o, const String& e, size_t& i) const;
	void convert_function(Vec& s, const String& e, size_t& i) const;
	void convert_operator(Vec& o, Vec& s, const String& e, size_t i) const;
	void convert_left_bracket(Vec& s, const String& e, size_t& i) const;
	void convert_right_bracket(Vec& s, Vec& o) const;
	void convert_separator(Vec& o, Vec& s) const;
	void convert_brackets_content(Vec& s, Vec& o) const;

	void parse_digit(Vec& s, const String& d) const;
	void parse_operator(Vec& s, const String& d) const;
	void parse_constant(const Operator& op, Real& result) const;
	void parse_binary(Vec& s, Operator& op, Real& result) const;
	void parse_unary(Vec& s, Operator& op, Real& result) const;

	bool get_operator(const String& name, Operator& op) const;
	String get_result(const Vec& str) const;

	template<typename T>
	void push_token(Vec& vec, const String& e, size_t& i, T pred) const;
};

#include "parser.ipp"

#endif
