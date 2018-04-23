#pragma once

#include "Thread.h"
#include <Core/Misc/CoreTypes.h>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {

	// atomics

	bool_a stop;

	uint16_a task_count;
	
	// members
	
	std::condition_variable condition;
	
	std::mutex mutex;
	
	std::queue<std::function<void ()>> tasks;
	
	std::vector<std::thread> workers;

public:

	// constructors

	ThreadPool (size_t threads);

	~ThreadPool ();
	
	// methods
	
	void Schedule (std::function<void ()> task);
	
	void WaitAll () const;

};