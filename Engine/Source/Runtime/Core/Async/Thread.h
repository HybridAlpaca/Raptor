#pragma once

#include <Core/Misc/Required.h>

#include <mutex>
#include <thread>

namespace Core
{
namespace Async
{

class Thread
{

	std::mutex mutex;

	bool_a shouldStop;

	std::thread thread;
	
	/// function for the thread to run
	void WorkerFunction ();
	
	/// delete copy constructor
	Thread (const Thread &) = delete;

	/// delete assignment operator
	Thread & operator= (const Thread &) = delete;

public:

	Thread ();
	
	~Thread ();
	
	void Start ();
	
	void Stop ();

};

}
}