//Question 2 - threads & synchronization

//Task: Improve execution time by using multi-threading instead of calling operation1 and operation2 serially, make sure that sum=EXPECTED_SUM after using threads
// please explain the changes you made and what new aspects you had to deal with when shifting from serial execution to parallel execution 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify the constexpr variables

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>            //use mutex to get sum with op1 and op2
using namespace std;

constexpr size_t ITERATIONS = 1000 * 1000ULL;
constexpr size_t OP1_PARAM = 2ULL;
constexpr size_t OP2_PARAM = 1ULL;
constexpr size_t EXPECTED_SUM = 1000001000000ULL;

size_t sum = 0;
std::mutex m;

void operation1(size_t arg) {
	std::cout << "Performing operation1" << std::endl;
	m.lock();                               //lock m when op1 get sum (let op2 wait)
	for (size_t i = 0; i < ITERATIONS; i++) {
		sum += (arg + i);
	}
	m.unlock();                             //unlock m , op2 can get to sum
	std::this_thread::sleep_for(std::chrono::seconds(5)); //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}


void operation2(size_t arg) {
	std::cout << "Performing operation2" << std::endl;
	m.lock();
	for (size_t i = 0; i < ITERATIONS; i++) {
		sum += (arg * i);
	}
	m.unlock();                             //unlock m , op1 can get to sum
	std::this_thread::sleep_for(std::chrono::seconds(10));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}


int main(int argc, char** argv)
{ //In this case we have sum the is shared with operation 1 and 2 , use mutex for get the sum for op1 and op2
	//the problem was that we need to get sum in the same time with op1,op2 , we can't do that , the sum !=EXPECTED_SUM
	//the solution is using thread , run operation1 and operation2 in the same time , but to change the sum we have to lock it.
	auto start = std::chrono::steady_clock::now();
	/*operation1(OP1_PARAM);
	operation2(OP2_PARAM);*/
	std::thread t1(operation1, OP1_PARAM);
	std::thread t2(operation2, OP2_PARAM);
	t1.join();
	t2.join();
	auto end = std::chrono::steady_clock::now();

	std::cout << "Total execution duration in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
	std::cout << "Result:  " << sum << ", " << (sum == EXPECTED_SUM ? "success" : "failure!") << std::endl;
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}