#include "ThreadPool.h"

#include <Core/Misc/CoreTypes.h>

#include <functional>
#include <mutex>

ThreadPool::ThreadPool (size_t threads) : stop(false), task_count(0u) {

	for (size_t i = 0; i < threads; i++) {
	
		workers.emplace_back([this] () -> void {
		
			while (true) {
			
				std::function<void ()> task;

				{
				
					std::unique_lock<std::mutex> lock(mutex);
					
					condition.wait(lock, [this] () -> bool {
					
						return !tasks.empty() || stop;
					
					});
					
					if (stop && tasks.empty())
						return;
						
					task = std::move(tasks.front());
					tasks.pop();
				
				}
				
				task();
				
				--task_count;
			
			}
		
		});
	
	}

}

ThreadPool::~ThreadPool () {

	stop = true;
	condition.notify_all();
	
	for (auto & worker : workers)
		if (worker.joinable())
			worker.join();

}

void ThreadPool::Schedule (std::function<void ()> task) {

	{
	
		std::unique_lock<std::mutex> lock(mutex);
		tasks.push(task);
	
	}
	
	++task_count;
	condition.notify_one();

}

void ThreadPool::WaitAll () const {

	while (task_count != 0u)
		std::this_thread::yield();

}