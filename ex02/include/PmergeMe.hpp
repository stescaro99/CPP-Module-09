#ifndef PMERGEME_HPP
# define PMERGEME_HPP

//# include <strstream>
# include <string>
# include <exception>
# include <vector>
# include <deque>
# include <ostream>
# include <algorithm>
# include <sstream>
# include <iostream>
# include <ctime>

class PmergeMe
{
private:
	std::vector<int> _sqc;
	std::deque<int> _deq;
public:
	PmergeMe();
	PmergeMe(char *ag[]);
	PmergeMe(const PmergeMe &org);
	~PmergeMe();

	void makeVec();
	void makeDeq();
	
	class NotValidNumber : public std::exception
	{
		public:
			const char *what() const throw();
	};

	template <typename T>
	void printRight(T &container);


	template <typename T>
	T mergeSort(T container);

	PmergeMe &operator=(const PmergeMe &org);
};



#endif