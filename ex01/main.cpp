#include <iostream>
#include "RPN.hpp"

int checkBigNumbers(const std::string &str)
{
	for (size_t i = 0; i < str.length(); i++)
	{
		if (isdigit(str[i]))
		{
			if (i + 1 < str.length() && isdigit(str[i + 1]))
				return 1;
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2 || std::string(argv[1]).empty())
	{
		std::cerr << "Usage: " << argv[0] << " \"RPN expression\"" << std::endl;
		return 1;
	}
	if (checkBigNumbers(argv[1]))
	{
		std::cerr << "Error: Numbers must be single-digit." << std::endl;
		return 1;
	}
	RPN rpn;
	rpn.evalAndPrint(argv[1]);
	return 0;
}
