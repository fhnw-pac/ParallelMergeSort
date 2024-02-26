#include "MergeSort.h"
#include <chrono>
#include <thread>
#include <cassert>
#include <random>
#include <omp.h>

void MergeSort::mMerge(std::vector<int>& a, uint64_t beg, uint64_t m, uint64_t end)
{
	std::vector<int> b(end - beg, 0);
	uint64_t i = 0, j = beg, k = m;
	while (j < m && k < end)
		if (a[j] <= a[k])
			b[i++] = a[j++];
		else
			b[i++] = a[k++];
	
	while (j < m)
		b[i++] = a[j++];

	while(i>0) {
		--i;
		a[beg + i] = b[i];
	}
}

void MergeSort::mSort(std::vector<int>& a, uint64_t beg, uint64_t end)
{
	if (end - beg > 1) {
		uint64_t m = (beg + end) >> 1;
		mSort(a, beg, m);
		mSort(a, m, end);
		mMerge(a, beg, m, end);
	}
}

void MergeSort::seqMSort(std::vector<int>& a)
{
	mSort(a, 0, a.size());
}

void MergeSort::parMSort(std::vector<int>& a)
{
	assert(a.size() % NO_OF_THREADS == 0);
	
	// TODO implement parallel merge sort with std::thread

	throw "NOT_IMPLEMENTED";
}

void MergeSort::ompMSort(std::vector<int>& a)
{
	assert(a.size() % NO_OF_THREADS == 0);

	// TODO implement parallel merge sort with OMP

	throw "NOT_IMPLEMENTED";
}

uint64_t MergeSort::measuredSort(std::vector<int>& a, void(MergeSort::*sortFunc)(std::vector<int>& a))
{
	auto start = std::chrono::high_resolution_clock::now();

	(this->*sortFunc)(a);

	auto stop = std::chrono::high_resolution_clock::now();

	return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}


uint64_t MergeSort::seqMergeSort(std::vector<int>& a)
{
	return measuredSort(a, &MergeSort::seqMSort);
}

uint64_t MergeSort::parMergeSort(std::vector<int>& a)
{
	return measuredSort(a, &MergeSort::parMSort);
}

uint64_t MergeSort::ompMergeSort(std::vector<int>& a)
{
	return measuredSort(a, &MergeSort::ompMSort);
}

bool MergeSort::prove(std::vector<int>& a)
{
	for (uint64_t i = 0; i < a.size() - 1; ++i) {
		if (a[i] > a[i + 1])
			return false;
	}

	return true;
}

bool MergeSort::equal(std::vector<int>& a, std::vector<int>& b)
{
	assert(a.size() == b.size());
	bool ret = true;

	for (int i = 0; i < a.size(); ++i) {
		ret &= a[i] == b[i];
	}

	return ret;
}

std::vector<int> MergeSort::createRandomData(uint64_t size) {

	std::vector<int> data(size, 0);

	// random gen
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, (int)size);
	generator.seed((unsigned)std::chrono::system_clock::now().time_since_epoch().count());

	for (int i = 0; i < size; ++i) {
		data[i] = distribution(generator);
	}

	return data;
}
