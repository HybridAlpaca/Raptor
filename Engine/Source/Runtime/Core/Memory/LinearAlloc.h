#pragma once

#include <Core/Misc/Required.h>

namespace Core
{
namespace Memory
{

class LinearAllocator
{

	size_t
		bufferSize = 0,
		memoryPeak = 0,
		memoryUsed = 0,
		offset = 0;
		
	void * startPtr = nullptr;

public:

	LinearAllocator (const size_t buffer_size);
	
	~LinearAllocator ();
	
	void * Allocate (const size_t allocation_size, const size_t alignment);
	
	void Destroy ();
	
	void Free (void * data) { ASSERT(false, "use `LinearAllocator::Reset` instead"); }
	
	void Reset ();

};

}
}