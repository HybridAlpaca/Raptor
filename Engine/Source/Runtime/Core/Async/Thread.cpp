#include "Thread.h"

#include <thread>
#include <mutex>

Thread::Thread (void (* function)(std::mutex &), std::mutex & mutex) {

	thread = std::thread(function, std::ref(mutex));

}

Thread::~Thread () {

	Join();

}

void Thread::Join () {

	if (thread.joinable())
		thread.join();

}

void Thread::Detach () {

	if (thread.joinable())
		thread.detach();

}