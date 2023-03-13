#include <iostream>
#include "MergeSort.h"
#include <random>
#include <chrono>

int main() {

	MergeSort m;
	const uint64_t size = ((32 * 1024 * 1024) / NO_OF_THREADS) * NO_OF_THREADS;

	auto seqData = m.createRandomData(size);
	std::vector<int> parData(seqData);

	double seqTime = m.seqMergeSort(seqData);
	if (!m.proove(seqData)) {
		std::cout << "seq sort did not sort..." << std::endl;
		exit(-42);
	}

	double parTime = m.parMergeSort(parData);
	if (!m.proove(parData)) {
		std::cout << "par sort did not sort..." << std::endl;
		exit(-42);
	}

	std::cout << "sorted seq in " << seqTime << "ms" << std::endl;
	std::cout << "sorted par in " << parTime << "ms" << std::endl;
	std::cout << "speedup is " << seqTime / parTime << std::endl;
}
