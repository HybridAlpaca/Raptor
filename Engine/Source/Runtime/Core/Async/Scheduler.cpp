#include "Scheduler.h"

#include <algorithm>
#include <string>

using Core::Async::Scheduler;

Scheduler::Scheduler ()
{
	// does XXX operation
}

Scheduler::~Scheduler ()
{
	Destroy();
}

void Scheduler::Destroy ()
{
	// TODO
}

void Scheduler::Emit (std::string id)
{
	// TODO
}

void Scheduler::Emit (std::string id, void * data)
{
	// TODO
}

void Scheduler::Subscribe (std::string id, Callback callback)
{
	callbacks[id].push_back(callback);
}

void Scheduler::Unsubscribe (std::string id)
{
	if (!callbacks.count(id))
	{
		// No callbacks with given ID,
		// so do nothing
		return;
	}
	callbacks.erase(id);
}

void Scheduler::Unsubscribe (std::string id, Callback callback)
{
	if (!callbacks.count(id))
	{
		// No callbacks with given ID,
		// so do nothing
		return;
	}
	callbacks[id].erase(std::remove(callbacks[id].begin(), callbacks[id].end(), callback), callbacks[id].end());
}
