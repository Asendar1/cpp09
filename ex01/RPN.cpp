#include "RPN.hpp"

RPN::RPN()
{

}

RPN::~RPN()
{

}

RPN::RPN(const RPN &other)
{
	_stack = other._stack;
}

RPN &RPN::operator=(const RPN &other)
{
	_stack = other._stack;
	return *this;
}

void RPN::evalAndPrint(const std::string &str)
{
	int result = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ')
			continue;
		else if (str[i] >= '0' && str[i] <= '9')
			_stack.push(str[i] - '0');
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			if (_stack.size() < 2)
			{
				std::cerr << "Error: Not enough operands for operation '" << str[i] << "'" << std::endl;
				return;
			}
			int b = _stack.top(); _stack.pop();
			int a = _stack.top(); _stack.pop();
			switch (str[i])
			{
				case '+': result = a + b; break;
				case '-': result = a - b; break;
				case '*': result = a * b; break;
				case '/':
					if (b == 0)
					{
						std::cerr << "Error: Division by zero" << std::endl;
						return;
					}
					result = a / b; break;
			}
			_stack.push(result);
		}
		else
		{
			std::cerr << "Error: Invalid character '" << str[i] << "'" << std::endl;
			return;
		}
	}
	if (_stack.size() != 1)
	{
		std::cerr << "Error: Invalid RPN expression" << std::endl;
		return;
	}
	std::cout << _stack.top() << std::endl;
}
