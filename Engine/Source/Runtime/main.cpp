#include <Core/Async/Thread.h>

#include <iostream>
#include <mutex>

void Worker (std::mutex & mutex) {

	static int id = 0;
	
	std::lock_guard<std::mutex> guard(mutex);
	
	std::cout << "Worker " << id++ << "\n";

}

int main () {

	std::mutex mutex;

	Thread thread0(Worker, mutex);
	Thread thread1(Worker, mutex);

	return 0;

}