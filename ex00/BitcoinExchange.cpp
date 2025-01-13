#include "BitcoinExchange.hpp"

short ft_perror(std::string error)
{
	std::cerr << error;
	return (1);
}

BitcoinExchange::BitcoinExchange()
{
	std::cout << "BitcoinExchange default constructor called" << std::endl;
	std::ifstream file("data.csv");
	if (!file)
	{
		ft_perror("Error: File does not exist\n");
		throw std::exception();
	}
	std::string line;
	std::string date;
	float rate;

	while (std::getline(file, line))
	{
		date = line.substr(0, line.find(','));
		std::stringstream(line.substr(line.find(',') + 1)) >> rate;
		this->exchangeRate[date] = rate;
	}
	file.close();
}

BitcoinExchange::~BitcoinExchange()
{
	std::cout << "BitcoinExchange default destructor called" << std::endl;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	std::cout << "BitcoinExchange copy constructor called" << std::endl;
	*this = copy;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	std::cout << "BitcoinExchange assignation operator called" << std::endl;
	if (this != &copy)
	{
		this->exchangeRate = copy.exchangeRate;
	}
	return (*this);
}

static bool checkRealDate(const std::string &date)
{
	short year, month, day;
	std::stringstream(date.substr(0, 4)) >> year;
	std::stringstream(date.substr(5, 2)) >> month;
	std::stringstream(date.substr(8, 2)) >> day;

	if (month < 1 || month > 12)
		return (false);
	switch (month)
	{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			if (day < 1 || day > 31)
				return (false);
			break;
		}
		case 4:
		case 6:
		case 9:
		case 11:
		{
			if (day < 1 || day > 30)
				return (false);
			break;
		}
		case 2:
		{
			if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
			{
				if (day < 1 || day > 29)
					return (false);
			}
			else
			{
				if (day < 1 || day > 28)
					return (false);
			}
			break;
		}
	}
	return (true);
}

static bool check(const std::string &input)
{
	int i = 0;
	bool dot = false;
	while (input[i])
	{
		if (i < 4 || (i > 4 && i < 7) || (i > 7 && i < 10))
		{
			if (input[i] < '0' || input[i] > '9')
				return (false);
		}
		else if (i == 4 || i == 7)
		{
			if (input[i] != '-')
				return (false);
		}
		else if (i == 10 || i == 12)
		{
			if (input[i] != ' ')
				return (false);
		}
		else if (i == 11)
		{
			if (input[i] != '|')
				return (false);
		}
		else if (i == 13)
		{
			if ((input[i] < '0' || input[i] > '9') && input[i] != '+' && input[i] != '-')
				return (false);
		}
		else
		{
			if ((input[i] < '0' || input[i] > '9') && (input[i] != '.' || dot))
				return (false);
			if (input[i] == '.')
				dot = true;
		}
		i++;
	}
	return (checkRealDate(input.substr(0, 10)));
}

std::string BitcoinExchange::nearestLowerDate(std::string date) const
{
	std::string nearestDate = "";
	for (std::map<std::string, float>::const_iterator it = this->exchangeRate.begin(); it != this->exchangeRate.end(); it++)
	{
		if (it->first <= date)
		{
			nearestDate = it->first;
		}
	}
	return (nearestDate);
}

void BitcoinExchange::exchange(const std::string &input) const
{
	if (input.size() < 1 || !check(input))
	{
		ft_perror("Error: Bad input => " + input + "\n");
		return ;
	}
	std::string date = input.substr(0, input.find(' '));
	float value;
	std::stringstream(input.substr(input.find(' ') + 2)) >> value; //+3???
	if (value < 0)
	{
		ft_perror("Error: not a positive number.\n");
		return ;
	}
	else if (value -1000 > 0)
	{
		ft_perror("Error: too large number.\n");
		return ;
	}

	std::string nearestDate = this->nearestLowerDate(date);
	if (nearestDate == "")
	{
		ft_perror("Error: No exchange rate available for this date\n");
		return ;
	}
	std::cout << date << " => " << value << " = " << value * this->exchangeRate.at(nearestDate) << std::endl;
}