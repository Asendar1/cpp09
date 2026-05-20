#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) { *this = other; }
PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		_vec = other._vec;
		_deq = other._deq;
	}
	return *this;
}

bool PmergeMe::parseArguments(int ac, char **av) {
	for (int i = 1; i < ac; ++i) {
		std::string arg = av[i];
		if (arg.empty()) return false;

		for (size_t j = 0; j < arg.length(); ++j) {
			if (!isdigit(arg[j])) return false;
		}

		long num = std::atol(arg.c_str());
		if (num > 2147483647) return false;

		_vec.push_back(static_cast<int>(num));
		_deq.push_back(static_cast<int>(num));
	}
	return !_vec.empty();
}

static size_t getJacobsthal(size_t n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	return getJacobsthal(n - 1) + 2 * getJacobsthal(n - 2);
}

void PmergeMe::fordJohnsonVector(std::vector<int>& arr) {
	if (arr.size() <= 1) return;

	std::vector<std::pair<int, int> > pairs;
	std::vector<int> mainChain;
	std::vector<int> pendElements;
	int oddElement = -1;
	bool hasOdd = (arr.size() % 2 != 0);

	for (size_t i = 0; i < arr.size() - 1; i += 2) {
		if (arr[i] < arr[i + 1])
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
		else
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	}
	if (hasOdd) {
		oddElement = arr.back();
	}

	for (size_t i = 0; i < pairs.size(); ++i) {
		mainChain.push_back(pairs[i].first);
	}
	fordJohnsonVector(mainChain);

	for (size_t i = 0; i < mainChain.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (mainChain[i] == pairs[j].first) {
				pendElements.push_back(pairs[j].second);
				break;
			}
		}
	}

	if (!pendElements.empty()) {
		mainChain.insert(mainChain.begin(), pendElements[0]);
	}

	size_t jIndex = 3;
	size_t lastInserted = 1;

	while (lastInserted < pendElements.size()) {
		size_t jacobValue = getJacobsthal(jIndex);
		if (jacobValue > pendElements.size()) {
			jacobValue = pendElements.size();
		}

		for (size_t i = jacobValue; i > lastInserted; --i) {
			std::vector<int>::iterator target = std::lower_bound(mainChain.begin(), mainChain.end(), pendElements[i - 1]);
			mainChain.insert(target, pendElements[i - 1]);
		}

		lastInserted = jacobValue;
		jIndex++;
	}

	if (hasOdd) {
		std::vector<int>::iterator target = std::lower_bound(mainChain.begin(), mainChain.end(), oddElement);
		mainChain.insert(target, oddElement);
	}

	arr = mainChain;
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& arr) {
	if (arr.size() <= 1) return;

	std::deque<std::pair<int, int> > pairs;
	std::deque<int> mainChain;
	std::deque<int> pendElements;
	int oddElement = -1;
	bool hasOdd = (arr.size() % 2 != 0);

	for (size_t i = 0; i < arr.size() - 1; i += 2) {
		if (arr[i] < arr[i + 1])
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
		else
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
	}
	if (hasOdd) oddElement = arr.back();

	for (size_t i = 0; i < pairs.size(); ++i) mainChain.push_back(pairs[i].first);
	fordJohnsonDeque(mainChain);

	for (size_t i = 0; i < mainChain.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (mainChain[i] == pairs[j].first) {
				pendElements.push_back(pairs[j].second);
				break;
			}
		}
	}

	if (!pendElements.empty()) mainChain.push_front(pendElements[0]);

	size_t jIndex = 3;
	size_t lastInserted = 1;

	while (lastInserted < pendElements.size()) {
		size_t jacobValue = getJacobsthal(jIndex);
		if (jacobValue > pendElements.size()) jacobValue = pendElements.size();

		for (size_t i = jacobValue; i > lastInserted; --i) {
			std::deque<int>::iterator target = std::lower_bound(mainChain.begin(), mainChain.end(), pendElements[i - 1]);
			mainChain.insert(target, pendElements[i - 1]);
		}
		lastInserted = jacobValue;
		jIndex++;
	}

	if (hasOdd) {
		std::deque<int>::iterator target = std::lower_bound(mainChain.begin(), mainChain.end(), oddElement);
		mainChain.insert(target, oddElement);
	}
	arr = mainChain;
}

void PmergeMe::runSort() {
	std::cout << "Before: ";
	for (size_t i = 0; i < _vec.size(); ++i) std::cout << _vec[i] << " ";
	std::cout << std::endl;

	clock_t startVec = clock();
	fordJohnsonVector(_vec);
	clock_t endVec = clock();

	clock_t startDeq = clock();
	fordJohnsonDeque(_deq);
	clock_t endDeq = clock();

	std::cout << "After:  ";
	for (size_t i = 0; i < _vec.size(); ++i) std::cout << _vec[i] << " ";
	std::cout << std::endl;

	double timeVec = static_cast<double>(endVec - startVec) / CLOCKS_PER_SEC * 1000.0;
	double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000.0;

	std::cout << "Time to process a range of " << _vec.size() << " elements with std::vector : " << timeVec << " us" << std::endl;
	std::cout << "Time to process a range of " << _deq.size() << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}
