#include <iostream>
#include <stack>

class RPN
{
	private:
		std::stack<int> _stack;
	public:
		RPN();
		~RPN();
		RPN(const RPN &other);
		RPN &operator=(const RPN &other);

		void evalAndPrint(const std::string &str);
};
