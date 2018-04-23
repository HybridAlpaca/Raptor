#include <Core/Async/ThreadPool.h>

#include <iostream>

void Worker () {

	static int id = 0;
	
	std::cout << "Worker " << id++ << "\n";

}

int main () {

	std::cout << "Create thread pool" << "\n";

	ThreadPool thread_pool(4);
	
	std::cout << "Schedule jobs" << "\n";
	
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	
	thread_pool.WaitAll();
	
	std::cout << "Exit" << "\n";

	return 0;

}