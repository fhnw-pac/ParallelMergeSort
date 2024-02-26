#include "MergeSort.h"
#include <iostream>
#include <random>
#include <chrono>

int main() {

	MergeSort m;
	const uint64_t size = ((32 * 1024 * 1024) / NO_OF_THREADS) * NO_OF_THREADS;

	auto seqData = m.createRandomData(size);
	std::vector<int> parData(seqData);
	std::vector<int> ompData(seqData);

	uint64_t seqTime = m.seqMergeSort(seqData);
	if (!m.prove(seqData)) {
		std::cout << "seq sort did not sort..." << std::endl;
		exit(-42);
	}

	uint64_t parTime = m.parMergeSort(parData);
	if (!m.equal(seqData, parData)) {
		std::cout << "par sort did not sort..." << std::endl;
		exit(-42);
	}

	uint64_t ompTime = m.ompMergeSort(ompData);
	if (!m.equal(seqData, ompData)) {
		std::cout << "omp sort did not sort..." << std::endl;
		exit(-42);
	}

	std::cout << "sorted seq in " << seqTime << "ms" << std::endl;
	std::cout << "sorted par in " << parTime << "ms" << std::endl;
	std::cout << "sorted omp in " << ompTime << "ms" << std::endl;
	std::cout << "speedup thr is " << (double)seqTime / parTime << std::endl;
	std::cout << "speedup omp is " << (double)seqTime / ompTime << std::endl;
}
