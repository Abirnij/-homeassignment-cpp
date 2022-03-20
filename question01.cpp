//Question 1 - basic STL

//Task 1: improve fill_vector and vecOfVec.push_back performance - execution time can be reduced significantly, please explain the changes you made and how they improve
// the application performance.

//Task 2: Implement count_total_elements without using a "visible" for loop

//Task 3: Implement merge_vec_of_vec 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify ELEMENT_COUNT and ITERATIONS and functions fill_vector,count_total_elements and merge_vec_of_vec function signatures  

#include <chrono>
#include <iostream>
#include <vector>

constexpr size_t ELEMENT_COUNT = 1000 * 10000;
constexpr size_t ITERATIONS = 10;

std::vector<uint64_t> fill_vector(size_t elementCount) {
	//TODO: improve function performance
	std::vector<uint64_t> vec;
	vec.reserve(elementCount); //it make allocate memory once and dont have to check every time if we need to reallocate
	for (size_t i = 0; i < elementCount; i++) {
		vec.push_back(i);
	}
	return vec;
}

/// This function should return the total elements in all of the vectors
size_t count_total_elements(const std::vector<std::vector<uint64_t>>& vecOfVec) {
	size_t count = 0;
	//count += vecOfVec.size(); 
	size_t i = 0;
	while (i != vecOfVec.size())
	{
		count += vecOfVec[i].size();
		i++;
	}

	/*while (!vecOfVec.empty())   it can't work because it is const!
	{
		count += vecOfVec.back().size();
		vecOfVec.pop_back();
	}*/
	return count; //TODO: replace with your code
}

/// This function should return a single vector that contain all of the elements of the vectors in vecOfVec
std::vector<uint64_t> merge_vec_of_vec(std::vector<std::vector<uint64_t>>& vecOfVec) {
	std::vector<uint64_t> mergedVec;
	size_t i = 0;
    size_t c = count_total_elements(vecOfVec);
	mergedVec.reserve(c);                                ////////bad malloc////////////////////
	for (;i < vecOfVec.size(); i++) 
	{
		for (size_t j = 0; j < vecOfVec[i].size(); j++)
		{
			mergedVec.push_back(vecOfVec[i][j]);  //insert the elment in each vector
		}
	}
	//TODO: Your code here
	return mergedVec;
}

int main(int argc, char** argv)
{
	//Create vector of vectors
	std::vector<std::vector<uint64_t>> vecOfVec;
	auto start = std::chrono::steady_clock::now();
	vecOfVec.reserve(ITERATIONS);    //allocate memory once for ITERATIONS elments
	for (size_t i = 0; i < ITERATIONS; i++) {
		std::vector<uint64_t> vec = fill_vector(ELEMENT_COUNT);
		//TODO: improve inserting performance
		vecOfVec.push_back(vec);
	}
	auto end = std::chrono::steady_clock::now();
	size_t averageIterationTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / ITERATIONS;
	std::cout << "Average iteration duration in microseconds: " << averageIterationTimeUs << std::endl;

	//Count elements
	size_t totalElements = count_total_elements(vecOfVec);
	std::cout << "Total elements in vecOfVec: " << totalElements << " " << std::endl;

	//Merge vector of vectors
	std::vector<uint64_t> mergedVec = merge_vec_of_vec(vecOfVec);
	std::cout << "Total elements in merged mergedVec: " << mergedVec.size() << std::endl;

	std::cout << "Press enter to exit" << std::endl;
	//getchar();
	return 0;
}