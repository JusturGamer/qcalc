#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "parser.h"
#include "qcalc.h"

using namespace ::testing;
using namespace std;
using mpfr::mpreal;

class ParserTest : public Test
{
protected:
	Parser parser;

	void SetUp() override { add_operators(parser); }
};

class ToPostfixTest : public ParserTest {};
class CalculateTest : public ParserTest {};
class SetPrecisionTest : public ParserTest {};

class IsBinaryOperatorTest : public Test
{
protected:
	Parser parser;

	void SetUp() override
	{
		parser.add_operator("<", 2, Parser::Direction::left,
			[](mpreal x, mpreal y) { return x < y; });
		parser.add_operator("!", 3, Parser::Direction::right,
			[](mpreal x) { return !x; });
		parser.add_operator("pi", 3, Parser::Direction::left,
			[]() { return mpfr::const_pi(); });
	}
};

class IsUnaryOperatorTest : public IsBinaryOperatorTest {};
class IsConstantTest : public IsBinaryOperatorTest {};

TEST_F(ToPostfixTest, HandlesEmptyStringInput) {
	ASSERT_THAT(parser.to_postfix(""), ElementsAre());
}

TEST_F(ToPostfixTest, RetainsSoleTokenOfOneTokenExpression) {
	ASSERT_THAT(parser.to_postfix("+"), ElementsAre("+"));
}

TEST_F(ToPostfixTest, IgnoresSpaces) {
	ASSERT_THAT(parser.to_postfix(" 2 "), ElementsAre("2"));
}

TEST_F(ToPostfixTest, TreatsMultiDigitNumberAsASingleToken) {
	ASSERT_THAT(parser.to_postfix("1234"), ElementsAre("1234"));
}

TEST_F(ToPostfixTest, ThrowsAnExceptionOnBracketsMismatch) {
	ASSERT_THROW(parser.to_postfix("2*(2+2"), brackets_mismatch);
}

TEST_F(ToPostfixTest, HandlesUnaryMinus) {
	ASSERT_THAT(parser.to_postfix("-2"), ElementsAre("0", "2", "-"));
}

TEST_F(ToPostfixTest, HandlesUnaryMinusAfterLeftBracket) {
	ASSERT_THAT(parser.to_postfix("(-2)"), ElementsAre("0", "2", "-"));
}

TEST_F(ToPostfixTest, HandlesSubtraction) {
	ASSERT_THAT(parser.to_postfix("2-3"), ElementsAre("2", "3", "-"));
}

TEST_F(ToPostfixTest, ConvertsInputToPostfixNotation) {
	ASSERT_THAT(parser.to_postfix("(2+3)*5"),
		ElementsAre("2", "3", "+", "5", "*"));
}

TEST_F(ToPostfixTest, HandlesFunctions) {
	ASSERT_THAT(parser.to_postfix("sin(max(2, 3)/3*pi)"),
		ElementsAre("2", "3", "max", "3", "/", "pi", "*", "sin"));
}

TEST_F(CalculateTest, HandlesEmptyInput) {
	ASSERT_THAT(parser.calculate({}), Eq(""));
}

TEST_F(CalculateTest, RetainsSoleTokenOfOneTokenExpression) {
	ASSERT_THAT(parser.calculate({ "2" }), Eq("2"));
}

TEST_F(CalculateTest, HandlesNegativeResult) {
	ASSERT_THAT(parser.calculate({"2", "3", "-"}), Eq("-1"));
}

TEST_F(CalculateTest, ThrowsAnExceptionOnDivisionByZero) {
	ASSERT_THROW(parser.calculate({ "2", "0", "/" }), division_by_zero);
}

TEST_F(CalculateTest, ThrowsAnExceptionOnUnknowFunction) {
	ASSERT_THROW(parser.calculate({ "abcd" }), unknow_function);
}

TEST_F(CalculateTest, CalculatesResult) {
	ASSERT_THAT(parser.calculate({ "3", "4", "5", "*", "+" }), Eq("23"));
}

TEST_F(CalculateTest, HandlesConstants) {
	parser.add_operator("two", 3, Parser::Direction::left,
		[]() { return 2; });

	ASSERT_THAT(parser.calculate({ "2", "two", "+" }), Eq("4"));
}

TEST_F(CalculateTest, HandlesUnaryFunctions) {
	parser.add_operator("sgn", 3, Parser::Direction::left,
		[](mpreal x) { return x < 0 ? -1 : x > 0 ? 1 : 0; });

	ASSERT_THAT(parser.calculate({ "2", "sgn" }), Eq("1"));
}

TEST_F(CalculateTest, HandlesBinaryFunctions) {
	parser.add_operator("max", 3, Parser::Direction::left,
		[](mpreal x, mpreal y) { return x > y ? x : y; });

	ASSERT_THAT(parser.calculate({ "3", "4", "+", "2", "8", "*", "max" }),
		Eq("16"));
}

TEST_F(CalculateTest, ThrowsAnExceptionOnMalformedExpression) {
	ASSERT_THROW(parser.calculate({ "2", "2", "/", "*" }),
		malformed_expression);
}

TEST_F(SetPrecisionTest, SetsPrecisionCorrectly) {
	parser.set_precision(2);

	ASSERT_THAT(parser.calculate({ "1", "3", "/" }), Eq("0.33"));
}

TEST_F(IsBinaryOperatorTest, ReturnsTrueOnBinaryOperators) {
	ASSERT_TRUE(parser.is_binary_operator("<"));
}

TEST_F(IsBinaryOperatorTest, ReturnsFalseIfNotABinaryOperator) {
	ASSERT_FALSE(parser.is_binary_operator("2"));
}

TEST_F(IsUnaryOperatorTest, ReturnsTrueOnUnaryOperators) {
	ASSERT_TRUE(parser.is_unary_operator("!"));
}

TEST_F(IsUnaryOperatorTest, ReturnsFalseIfNotAUnaryOperator) {
	ASSERT_FALSE(parser.is_unary_operator("<"));
}

TEST_F(IsConstantTest, ReturnsTrueOnConstant) {
	ASSERT_TRUE(parser.is_constant("pi"));
}

TEST_F(IsConstantTest, ReturnsFalseIfNotAConstant) {
	ASSERT_FALSE(parser.is_constant("!"));
}