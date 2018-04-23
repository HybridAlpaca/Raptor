#pragma once

#include <thread>
#include <mutex>

class Thread {

	std::thread thread;

public:

	Thread (void (* function)(std::mutex &), std::mutex & mutex);
	
	~Thread ();
	
	void Join ();
	
	void Detach ();

};