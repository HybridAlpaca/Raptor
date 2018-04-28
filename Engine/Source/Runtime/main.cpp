#include <Core/Async/ThreadPool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <thread>

void Worker () {
	
	std::cout << "Worker " << std::this_thread::get_id() << "\n";

}

int main () {

	std::cout << "Create thread pool" << "\n";

	ThreadPool thread_pool(4);
	
	std::cout << "Schedule jobs" << "\n";
	
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	
	thread_pool.WaitAll();
	
	std::cout << "Wait" << "\n";
	
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	thread_pool.Schedule(Worker);
	
	thread_pool.WaitAll();
	
	std::cout << "Exit" << "\n";

	return 0;

}