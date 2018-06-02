#pragma once

#include <Core/Common/Required.h>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace Core::Async
{

class Scheduler
{

	typedef std::function<void (void * data)> Task;

	std::condition_variable condition;

	std::mutex mutex;
	
	std::queue<Task> taskQueue;
	
	std::vector<std::thread> workers;
	
	uint8 numWorkers;
	
	bool_a shouldStop;
	
	uint16 task_count;
	
	/// Method for worker threads to run
	void WorkerTask ();

public:

	/// Max of 255 active threads
	Scheduler (uint8 num_threads);
	
	~Scheduler ();
	
	void Destroy ();
	
	void Schedule (Task task);
	
	void WaitAll ();

};

}