#include "GlobalStore.h"
#include "Utils.h"

#include <cstdlib>

using Core::Memory::GlobalStore;
using Core::Memory::CalculatePadding;

GlobalStore::GlobalStore (const size_t bufferSize)
: bufferSize(bufferSize)
{
	start = malloc(bufferSize);
	if ((start == NULL) || (start == nullptr))
	{
		FATAL("Not enough memory!  Requested " << bufferSize << " bytes for GS");
		return;
	}
	DEBUG("GS intial malloc: allocated " << bufferSize << " bytes");
	Reset();
}

GlobalStore::~GlobalStore ()
{
	Destroy ();
}

void * GlobalStore::Alloc (const size_t size, const size_t alignment)
{
	size_t padding = 0;
	size_t paddedAddr = 0;
	const size_t currentAddr = (size_t) start + offset;
	
	if (alignment != 0 && offset % alignment != 0)
	{
		// Alignment is necessary to allocate data.
		// Find next aligned addr and update offset
		padding = CalculatePadding(currentAddr, alignment);
	}
	
	if (offset + padding + size > bufferSize)
	{
		DEBUG("GS out of memory.  Requested: " << (offset + padding + size) << ", actual: " << bufferSize);
		return nullptr;
	}
	
	offset += padding;
	const size_t nextAddr = currentAddr + size;
	offset += size;
	
	memoryUsed = offset;
	memoryPeak = std::max(memoryPeak, memoryUsed);
	
	DEBUG("GS allocation: " << size + padding << " bytes allocated.  USED: "
	<< memoryUsed << ", FREE: " << (bufferSize - memoryUsed) << ", TOTAL: "
	<< bufferSize);
	
	return (void *) nextAddr;
}

void GlobalStore::Destroy ()
{
	if (start != nullptr)
	{
		DEBUG("GS destroy.  Potentially leaked: " << offset << " bytes");
		free(start);
		start = nullptr;
	}
	
	Reset();
	bufferSize = 0;
}

void GlobalStore::Reset ()
{
	offset = 0;
	memoryUsed = 0;
	memoryPeak = 0;
}