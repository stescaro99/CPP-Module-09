#include "PmergeMe.hpp"

int main(int ac, char *ag[])
{
	if (ac < 2 )
	{
		std::cerr << "error : at least 2 arguments required" << std::endl;
		return (1);
	}
	try
	{
		PmergeMe *merge = new PmergeMe(ag);

		merge->makeDeq();
		merge->makeVec();

		delete(merge);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

}