#include "BitcoinExchange.hpp"

static void firstLine(std::string line)
{
	std::string lowerLine;

	for (std::string::size_type i = 0; i < line.length(); i++)
		lowerLine += tolower(line[i]);

	if (lowerLine != "date | value")
		ft_perror("Warning: the format might be wrong\n");
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_perror("Error: Wrong number of arguments\n"));

	std::ifstream file(argv[1]);
	if (!file)
		return (ft_perror("Error: File does not exist\n"));

	try
	{
		std::string line;
		BitcoinExchange btc;
		getline(file, line);
		firstLine(line);
		while (getline(file, line))
		{
			btc.exchange(line);
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << std::endl;
	}
	
	file.close();
	return (0);
}

/* 
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-11-11 | -1
2001-42-42
2012-11-11 | 1
2012-11-11 | 2147483648
2012-01-01 | 1
2012-01-02 | 1
2012-01-03 | 1
2013-02-29 | 1
3600-02-29 | 1000.0001
3600-02-29 | 1000
3600-02-29 | 0.0
3600-02-29 | 10.0.3

1254-01-31 | 30
*/