#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iomanip>
#include <fstream>
#include <exception>
#include <sstream>

short ft_perror(std::string error);

class BitcoinExchange
{
	private:
		std::map<std::string, float> exchangeRate;
		std::string nearestLowerDate(std::string date) const;

	public:
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange &operator=(const BitcoinExchange &copy);

		void exchange(const std::string &input) const;
};

#endif