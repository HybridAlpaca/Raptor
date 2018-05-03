#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Core
{
namespace Async
{

class Scheduler
{

	typedef std::function<void (void * data)> Callback;

	// map of event ID's to their list of callbacks
	std::unordered_map<std::string, std::vector<Callback>> callbacks;

public:

	Scheduler ();
	
	~Scheduler ();
	
	void Destroy ();
	
	// fire event without data (i.e. notify listeners)
	void Emit (std::string id);
	
	// fire event with data
	void Emit (std::string id, void * data);
	
	void Subscribe (std::string id, Callback callback);
	
	// unsubscribe from all events from this ID
	void Unsubscribe (std::string id);
	
	// unsubscribe from a certain collback from this ID
	void Unsubscribe (std::string id, Callback callback);

};

}
}