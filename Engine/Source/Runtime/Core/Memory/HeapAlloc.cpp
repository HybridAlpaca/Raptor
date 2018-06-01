#include <Core/Common/Required.h>
#include "HeapAlloc.h"
#include "Utils.h"

#include <algorithm>
#include <cstdlib>
#include <limits>

using Core::Memory::HeapAllocator;
using Core::Memory::OptimizePolicy;

HeapAllocator::HeapAllocator (size_t bufferSize, OptimizePolicy policy)
: bufferSize(bufferSize), policy(policy)
{
	start = malloc(bufferSize);
	if (!start)
	{
		FATAL("Not enough memory!  Requested " << bufferSize << " bytes for heap");
		return;
	}
	DEBUG("Heap initial malloc: allocated " << bufferSize << " bytes");
	Reset();
}

HeapAllocator::~HeapAllocator ()
{
	Destroy();
}

void * HeapAllocator::Alloc (const size_t size, const size_t alignment = 0)
{
	const size_t allocHeaderSize = sizeof(AllocHeader);
	const size_t freeHeaderSize = sizeof(FreeHeader);
	
	ASSERT(size >= sizeof(Node), "Allocation size is too small");
	ASSERT(alignment >= 8, "Alignment must be at least 8 bits")
	
	size_t padding;
	Node * previous;
	Node * affected;
	
	Find(size, alignment, padding, previous, affected);
	
	if (!affected)
	{
		DEBUG("Heap out of memory.  Requested: " << (padding + size));
		return nullptr;
	}
	
	const size_t alignPadding = padding - allocHeaderSize;
	const size_t requiredSize = size + padding;
	const size_t rest = affected -> data.blockSize - requiredSize;
	
	if (rest > 0)
	{
		// Need to split current block into a data
		// block & another block of size `rest`
		
		Node * newFree = (Node *)((size_t) affected + requiredSize);
		newFree -> data.blockSize = rest;
		freeList.Insert(affected, newFree);
	}
	
	freeList.Remove(previous, affected);
	
	const size_t headerAddr = (size_t) affected + alignPadding;
	const size_t dataAddr = headerAddr + allocHeaderSize;
	
	((AllocHeader *) headerAddr) -> blockSize = requiredSize;
	((AllocHeader *) headerAddr) -> padding = alignPadding;
	
	memoryUsed += requiredSize;
	//memoryPeak = std::max(memoryPeak, memoryUsed);
	
	DEBUG("Heap allocation: " << size + padding << " bytes allocated.  USED: "
	<< memoryUsed << ", FREE: " << (bufferSize - memoryUsed) << ", TOTAL: "
	<< bufferSize);
	
	return (void *) dataAddr;
}

void HeapAllocator::Coalescence (Node * previous, Node * free)
{
	if (free -> next != nullptr && (size_t) free + free -> data.blockSize == (size_t) free -> next)
	{
		free -> data.blockSize += free -> next -> data.blockSize;
		freeList.Remove(free, free -> next);
	}

	if (previous != nullptr && (size_t) previous + previous -> data.blockSize == (size_t) free)
	{
		previous -> data.blockSize += free -> data.blockSize;
		freeList.Remove(previous, free);
	}	
}

void HeapAllocator::Destroy ()
{
	if (start)
	{
		DEBUG("Heap destroy.  Potentially leaked: " << memoryUsed << " bytes");
		free(start);
		start = nullptr;
	}
	bufferSize = 0;
}

void HeapAllocator::Find (const size_t size, const size_t alignment, size_t & padding, Node *& previous, Node *& found)
{
	switch (policy)
	{
		case OptimizePolicy::FIRST:
			FindFirst(size, alignment, padding, previous, found);
			break;
		case OptimizePolicy::BEST:
			FindBest(size, alignment, padding, previous, found);
			break;
		default:
			FATAL("Unknown HeapAllocator optimization policy");
			break;
	}
}

void HeapAllocator::FindBest (const size_t size, const size_t alignment, size_t & padding, Node *& previous, Node *& found)
{
	long long unsigned smallestDiff = 18446744073709551615u;
	Node * bestBlock = nullptr;
	Node * it = freeList.head;
	Node * itPrev = nullptr;
	
	while (it != nullptr)
	{
		padding = Core::Memory::CalculatePaddingWithHeader((size_t) it, alignment, sizeof (AllocHeader));
		const size_t requiredSpace = size + padding;
		if (it -> data.blockSize >= requiredSpace && (it -> data.blockSize - requiredSpace < smallestDiff))
		{
			// Found the best block
			bestBlock = it;
		}
		itPrev = it;
		it = it -> next;
	}
	
	previous = itPrev;
	found = bestBlock;
}

void HeapAllocator::FindFirst (const size_t size, const size_t alignment, size_t & padding, Node *& previous, Node *& found)
{
	FATAL("Requested memory policy not yet implemented.  Try `BEST` instead");
}

void HeapAllocator::Free (void * data)
{
	if (!data)
	{
		DEBUG("Heap requested to free invalid data");
		return;
	}

	const size_t currentAddr = (size_t) data;
	const size_t headerAddr = currentAddr - sizeof(AllocHeader);
	const AllocHeader * allocHeader{(AllocHeader *) headerAddr};
	
	Node * free = (Node *) headerAddr;
	free -> data.blockSize = allocHeader -> blockSize + allocHeader -> padding;
	free -> next = nullptr;
	
	Node * it = freeList.head;
	Node * itPrev = nullptr;
	
	while (it != nullptr)
	{
		if (data < it)
		{
			freeList.Insert(itPrev, free);
			break;
		}
		
		itPrev = it;
		it = it -> next;
	}
	
	memoryUsed -= free -> data.blockSize;
	DEBUG("Heap free: " << (free -> data.blockSize) << " bytes freed. USED: "
	<< memoryUsed << ", FREE: " << (bufferSize - memoryUsed) << ", TOTAL: "
	<< bufferSize);
	
	Coalescence(itPrev, free);
}

void HeapAllocator::Reset ()
{
	memoryUsed = 0;
	memoryPeak = 0;
	
	Node * firstNode = (Node *) start;
	firstNode -> data.blockSize = bufferSize;
	firstNode -> next = nullptr;
	
	freeList.head = nullptr;
	freeList.Insert(nullptr, firstNode);
}