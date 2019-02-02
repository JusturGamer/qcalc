template<typename T>
void Parser::add_operator(String n, int p, Direction d, T f)
{
	ops[n] = Operator{ p, d, f };
}

template<typename T>
void Parser::push_token(Vec& vec, const String& e, size_t& i, T pred) const
{
	String token;
	while (pred(e[i])) token += e[i++];
	vec.push_back(token);
	--i;
}

struct malformed_expression : public std::exception
{
	virtual const char* what() const noexcept override
	{
		return "Malformed exception";
	}
};

struct brackets_mismatch : public std::exception
{
	virtual const char* what() const noexcept override
	{
		return "Brackets mismatch";
	}
};

struct division_by_zero : public std::exception
{
	virtual const char* what() const noexcept override
	{
		return "Division by zero is undefined";
	}
};

struct unknow_function : public std::exception
{
	virtual const char* what() const noexcept override
	{
		return "Unknow function";
	}
};
