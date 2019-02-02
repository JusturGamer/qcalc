#include "qcalc.h"

using mpfr::mpreal;

void add_operators(Parser& parser)
{
	parser.add_operator("+", 1, Parser::Direction::left,
		[](mpreal x, mpreal y) { return x + y; });

	parser.add_operator("-", 1, Parser::Direction::left,
		[](mpreal x, mpreal y) { return x - y; });

	parser.add_operator("*", 2, Parser::Direction::left,
		[](mpreal x, mpreal y) { return x * y; });

	parser.add_operator("/", 2, Parser::Direction::left,
		[](mpreal x, mpreal y)
	{
		if (y == 0) throw division_by_zero{};
		return x / y;
	});
}
