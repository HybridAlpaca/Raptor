#include "Thread.h"

#include <thread>

using Core::Async::Thread;

Thread::Thread ()
	: shouldStop(false)
{
	thread = std::thread(& Thread::WorkerFunction, this);
}

Thread::~Thread ()
{
	Stop();
	
	if (thread.joinable())
	{
		// terminate the thread if we're able
		thread.join();
	}
}

void Thread::Start ()
{
	mutex.lock();
	
	shouldStop = false;
	
	mutex.unlock();
}

void Thread::Stop ()
{
	mutex.lock();
	
	shouldStop = true;
	
	mutex.unlock();
}

void Thread::WorkerFunction ()
{
	while (!shouldStop)
	{
		// perform XXX operation
	}
}