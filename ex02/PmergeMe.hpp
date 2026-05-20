#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class PmergeMe
{
	private:
		std::vector<int> _vec;
		std::deque<int>  _deq;

		void fordJohnsonVector(std::vector<int>& arr);
		void fordJohnsonDeque(std::deque<int>& arr);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe& operator=(const PmergeMe& other);
		~PmergeMe();

		bool parseArguments(int ac, char **av);
		void runSort();
};

#endif
