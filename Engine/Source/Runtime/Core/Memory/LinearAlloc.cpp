#include <Core/Common/Required.h>

#include "LinearAlloc.h"
#include "Utils.h"

#include <memory>

using Core::Memory::LinearAllocator;
using Core::Memory::CalculatePadding;

LinearAllocator::LinearAllocator (size_t buffer_size)
: bufferSize (buffer_size)
{
	startPtr = malloc(buffer_size);
}

LinearAllocator::~LinearAllocator ()
{
	Destroy ();
}

void LinearAllocator::Destroy ()
{
	Reset();

	free(startPtr);
	startPtr = nullptr;
}

void LinearAllocator::Reset ()
{
	memoryPeak = 0;
	memoryUsed = 0;
	offset = 0;
}