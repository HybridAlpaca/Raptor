#pragma once

#include <Core/Misc/Required.h>

#include "Utils.h"

namespace Core
{
namespace Memory
{

/**

USAGE

LinearAllocator allocator(2048);
Foo * foo = allocator.Allocate<Foo>();
allocator.Free<Foo>(foo);

**/

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
	
	template <typename Type>
	Type * Allocate ();
	
	void Destroy ();
	
	template <typename Type>
	void Free (Type * data) { FATAL("use `LinearAllocator::Reset` instead"); }
	
	size_t MemoryPeak () const { return memoryPeak; }
	
	size_t MemoryUsed () const { return memoryUsed; }
	
	void Reset ();

};

}

#include "LinearAlloc.hpp"
}