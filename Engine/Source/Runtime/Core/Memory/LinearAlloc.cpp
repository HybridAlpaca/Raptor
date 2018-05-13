#include <Core/Misc/Required.h>

#include "LinearAlloc.h"

#include <memory>

using Core::Memory::LinearAllocator;

LinearAllocator::LinearAllocator (size_t buffer_size)
: bufferSize (buffer_size)
{
	startPtr = malloc(buffer_size);
}

LinearAllocator::~LinearAllocator ()
{
	Destroy ();
}

void * LinearAllocator::Allocate (const size_t allocation_size, const size_t alignment)
{
	size_t
		padding = 0,
		paddedAddr = 0;
		
	const size_t currentAddr = (size_t) startPtr + offset;
	
	if (alignment != 0 && (offset % alignment != 0))
	{
		// memory alignment is required; calculate padding
	}
	
	if (offset + padding + allocation_size > bufferSize)
	{
		// allocation size exceeded max buffer size
		DEBUG("possible segfault avoided.  Watch your allocations!");
		return nullptr;
	}
	
	offset += padding;
	const size_t nextAddr = currentAddr + padding;
	
	offset += allocation_size;
	memoryUsed = offset;
	
	if (memoryUsed > memoryPeak)
	{
		memoryPeak = memoryUsed;
	}
	
	return (void *) nextAddr;
}

void LinearAllocator::Destroy ()
{
	free(startPtr);
	startPtr = nullptr;
}