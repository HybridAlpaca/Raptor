#pragma once

#include <Core/Common/Required.h>

namespace Core
{
namespace Memory
{

class GlobalStore
{
	size_t bufferSize;
	size_t memoryPeak;
	size_t memoryUsed;
	size_t offset;
	
	void * start = nullptr;

public:
	
	GlobalStore (const size_t bufferSize);
	GlobalStore (const GlobalStore & copy) = delete;
	
	~GlobalStore ();
	
	GlobalStore & operator= (const GlobalStore & copy) = delete;
	
	void * Alloc (const size_t size, const size_t alignment);
	
	void Destroy ();
	
	void Reset ();
	
	const size_t Size () const { return bufferSize; }
	const size_t Peak () const { return memoryPeak; }
	const size_t Used () const { return memoryUsed; }
};

}
}