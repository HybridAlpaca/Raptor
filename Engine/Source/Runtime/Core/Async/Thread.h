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

	std::thread thread;

public:

	Thread (Function function, std::mutex & mutex);
	
	~Thread ();
	
	bool Detach ();
	
	bool Join ();

};

}
}