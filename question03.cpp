//Question 3 - pointers

// There is a memory leak in the code below, where is it?, what class/solution can you use to fix it while ensuring that the object will be deleted only once and only when it's not used by any consumer
// Task: Modify the code to address the issues above. Please explain the changes you made and how they solve the memory allocation/deletion issue  

// Do not remove any function or change threads dispatching order - you can(and should) change the functions body/signature

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
 

//Evry time we use new we need delete .
//In this code we have pointer for new (struct) , and there is now delete , so we have memory leak
//We need to free(delete) the struck memory allocated , by using delete.

struct Payload {

	Payload(uint64_t id_) :
		id(id_),
		veryLargeVector(1000 * 1000)
	{}
	~Payload()    //destructor for the struct
	{
	}
	uint64_t id;
	std::vector<int> veryLargeVector;
};

void operation1(Payload* payload) {
	std::cout << "Performing operation1 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}

void operation2(Payload* payload) {
	std::cout << "Performing operation2 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1)))));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}

void dispacher_thread() {
	Payload* payload = new Payload(1);
	std::this_thread::sleep_for(std::chrono::seconds(2));  //Simulate some heavy work
	std::thread wt1(&operation1, payload);
	std::thread wt2(&operation2, payload);
	//Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
	wt1.detach();
	wt2.detach();
	//delete payload; //after detach wt1 ,wt2, we can delete the poyload 
					//I think it can't solve the problem beacuse we have detach (it wouldn't stop here).
					 //So I think that the solution is a destructor for the struct
	
}

int main(int argc, char** argv)
{
	std::cout << "Calling dispatcher thread" << std::endl;
	std::thread t(&dispacher_thread);
	t.join();
	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}