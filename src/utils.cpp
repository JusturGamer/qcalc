#include "utils.h"

void move_last_elem(std::vector<std::string>& d, std::vector<std::string>& s)
{
	d.push_back(s.back());
	s.pop_back();
}

bool is_bracket(const std::string& str)
{
	return str == "(" || str == ")";
}
