#include "RPN.hpp"

RPN::RPN()
{
	std::cout << "RPN default constructor called" << std::endl;
}

RPN::~RPN()
{
	std::cout << "RPN default destructor called" << std::endl;
}

RPN::RPN(const RPN &cpy)
{
	std::cout << "RPN copy constructor called" << std::endl;
	*this = cpy;
}

RPN &RPN::operator=(const RPN &cpy)
{
	std::cout << "RPN assignation operator called" << std::endl;
	if (this != &cpy)
	{
		this->stack = cpy.stack;
	}
	return (*this);
}

static bool check_overflow(int a, int b, char op)
{
	if (op == '+')
	{
		if (a > 0 && b > 0 && a + b < 0)
			return false;
		if (a < 0 && b < 0 && a + b > 0)
			return false;
	}
	else if (op == '-')
	{
		if (a > 0 && b < 0 && a - b < 0)
			return false;
		if (a < 0 && b > 0 && a - b > 0)
			return false;
	}
	else if (op == '*')
	{
		if (a > 0 && b > 0 && a * b < 0)
			return false;
		if (a < 0 && b < 0 && a * b < 0)
			return false;
		if (a > 0 && b < 0 && a * b > 0)
			return false;
		if (a < 0 && b > 0 && a * b > 0)
			return false;
	}
	else if (op == '/')
	{
		if (a > 0 && b > 0 && a / b < 0)
			return false;
		if (a < 0 && b < 0 && a / b < 0)
			return false;
		if (a > 0 && b < 0 && a / b > 0)
			return false;
		if (a < 0 && b > 0 && a / b > 0)
			return false;
	}
	return true;
}

void RPN::calculate(const std::string &input)
{
	int i = 0;
	int n;

	while (input[i])
	{
		if (input[i] >= '0' && input[i] <= '9')
		{
			n = input[i] - '0';
			this->stack.push(n);
		}
		else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
		{
			if (this->stack.size() < 2)
			{
				std::cerr << "Error: Too many operators!" << std::endl;
				return ;
			}
			int n2 = this->stack.top();
			this->stack.pop();
			int n1 = this->stack.top();
			this->stack.pop();
			if (input[i] == '+' && check_overflow(n1, n2, '+'))
				this->stack.push(n1 + n2);
			else if (input[i] == '-' && check_overflow(n1, n2, '-')) 
				this->stack.push(n1 - n2);
			else if (input[i] == '*' && check_overflow(n1, n2, '*'))
				this->stack.push(n1 * n2);
			else if (input[i] == '/' && n2 != 0 && check_overflow(n1, n2, '/'))
				this->stack.push(n1 / n2);
			else if (n2 == 0 && input[i] == '/')
			{
				std::cerr << "Error: Can't divide by zero!" << std::endl;
				return ;
			}
			else
			{
				std::cerr << "Error: Overflow!" << std::endl;
				return ;
			}
			// std::cout << n1 << " " << input[i] << " " << n2 << " = " << this->stack.top() << std::endl; // Debug
		}
		else if (input[i] != ' ')
		{
			std::cerr << "Error" << std::endl;
			return ;
		}
		i++;
	}
	if (this->stack.size() != 1)
	{
		std::cerr << "Error: Too many numbers!" << std::endl;
		return ;
	}
	std::cout << this->stack.top() << std::endl;
}