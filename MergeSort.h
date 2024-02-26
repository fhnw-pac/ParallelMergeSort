#pragma once
#include <vector>
#include <cmath>

// set to powers of 2
constexpr auto NO_OF_THREADS = 4;

class MergeSort
{
	static void mMerge(std::vector<int>& a, uint64_t beg, uint64_t m, uint64_t end);
	static void mSort(std::vector<int>& a, uint64_t beg, uint64_t end);

	void seqMSort(std::vector<int>& a);
	void parMSort(std::vector<int>& a);
	void ompMSort(std::vector<int>& a);

	uint64_t measuredSort(std::vector<int>& a, void(MergeSort::*sortFunc)(std::vector<int>& a));

public:

	uint64_t seqMergeSort(std::vector<int>& a);
	uint64_t parMergeSort(std::vector<int>& a);
	uint64_t ompMergeSort(std::vector<int>& a);
	bool prove(std::vector<int>& a);
	bool equal(std::vector<int>& a, std::vector<int>& b);
	std::vector<int> createRandomData(uint64_t size);
};
