#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <iomanip>

class RPN
{
	private:
		std::stack<int> stack;
	
	public:
		RPN();
		~RPN();
		RPN(const RPN &cpy);
		RPN &operator=(const RPN &cpy);

		void calculate(const std::string &input);
};

#endif
