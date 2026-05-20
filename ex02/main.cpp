#include "PmergeMe.hpp"

int main(int ac, char **av)
{
	if (ac < 2) {
		std::cout << "Error: Provide an integer sequence to sort." << std::endl;
		return 1;
	}

	PmergeMe sorter;
	if (!sorter.parseArguments(ac, av)) {
		std::cout << "Error" << std::endl;
		return 1;
	}

	sorter.runSort();
	return 0;
}
