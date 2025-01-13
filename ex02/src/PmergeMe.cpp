#include "PmergeMe.hpp"

PmergeMe::PmergeMe(): _sqc(0), _deq(0)
{

}

PmergeMe::~PmergeMe()
{
}

const char *PmergeMe::NotValidNumber::what() const throw()
{
	return "Not valid numeber found";
}

template <typename T>
void PmergeMe::printRight(T &container)
{
	for (typename T::iterator i = container.begin(); i != container.end(); i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

PmergeMe::PmergeMe(char *ag[])
{
	std::stringstream ss;
	int nbr;
	for (int i = 1; ag[i]; i++)
	{
		ss << ag[i];
		ss >> nbr;
		if (ss.fail() || nbr < 0)
			throw(NotValidNumber());
		_sqc.push_back(nbr);
		_deq.push_back(nbr);
		ss.clear();
		ss.str("");
	}
	std::cout << "Before: ";
	printRight(_sqc);
	std::vector<int> copy(_sqc);
	std::sort(copy.begin(), copy.end());
	std::cout << "After: ";
	printRight(copy);
}

PmergeMe::PmergeMe(const PmergeMe &org): _sqc(org._sqc)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &org)
{
	if (this != &org)
	{
		_sqc = org._sqc;
	}
	return (*this);
}

void PmergeMe::makeVec()
{
	std::vector<int> sort;
	clock_t start = clock();
	sort = mergeSort(_sqc);
	clock_t end = clock();
	std::cout << "Time to process a range of " << _sqc.size() << " elements with std::vector : " << end - start << " us" <<std::endl;
	//printRight(sort);
}
void PmergeMe::makeDeq()
{
	std::deque<int> sort;
	clock_t start = clock();
	sort = mergeSort(_deq);
	clock_t end = clock();
	std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque : " << end - start << " us" <<std::endl;
	//printRight(sort);
}

template <typename T>
T PmergeMe::mergeSort(T container)
{
	T max;
	T min;
	int first;
	int second;
	if(container.size() == 1)
		return(container);
	do
	{
		if (container.size() >= 2)
		{
			first = container.front();
			container.erase(container.begin());
			second = container.front();
			container.erase(container.begin());
			if (first > second)
			{
				max.push_back(first);
				min.push_back(second);
			}
			else
			{
				max.push_back(second);
				min.push_back(first);
			}
		}
		else if (container.size() == 1)
		{
			min.push_back(container.front());
			container.erase(container.begin());
		}
	} while(container.size());
	if (max.size() > 1)
		max = mergeSort(max);
	while(!min.empty())
	{
		int numb = min.front();
		typename T::iterator start = max.begin();
		typename T::iterator finish = max.end();
		while (start != finish)
		{
			typename T::iterator i = start;
			std::advance(i, std::distance(start,finish) / 2);
			if (numb < *i)
			{
				finish = i;
			}
			else
			{
				start = i;
				++start;
			}
		}
		max.insert(start, numb);
		min.erase(min.begin());
	}
	return (max);
}