#include <Core/Common/Required.h>
#include "BlobLoader.h"
#include "Utils.h"

#include <algorithm>
#include <cstdlib>
#include <limits>

using Core::Memory::BlobLoader;
using Core::Memory::OptimizePolicy;

BlobLoader::BlobLoader (size_t bufferSize, OptimizePolicy policy)
: bufferSize(bufferSize), policy(policy)
{	
	// Allocate buffer
	start = malloc(bufferSize);
	
	// Reset allocator
	Reset();
}

BlobLoader::~BlobLoader ()
{
	Destroy();
}

void * BlobLoader::Alloc (const size_t size, const size_t alignment = 0)
{
	const size_t allocHeaderSize = sizeof(AllocHeader);
	const size_t freeHeaderSize = sizeof(FreeHeader);
	
	ASSERT(size >= sizeof(Node), "Allocation size is too small");
	ASSERT(alignment >= 8, "Alignment must be at least 8 bits")
	
	size_t padding;
	Node * previous;
	Node * affected;
	
	Find(size, alignment, padding, previous, affected);
	
	ASSERT(affected != nullptr, "Not enough memory");
	
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
	memoryPeak = std::max(memoryPeak, memoryUsed);
	
	return (void *) dataAddr;
}

void BlobLoader::Coalescence (Node * previous, Node * free)
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

void BlobLoader::Destroy ()
{
	free(start);
	start = nullptr;
}

void BlobLoader::Find (const size_t size, const size_t alignment, size_t & padding, Node *& previous, Node *& found)
{
	switch (policy)
	{
		case OptimizePolicy::FIRST:
			FATAL("Selected policy not yet implemented.  Try using `BEST` instead.");
			break;
		case OptimizePolicy::BEST:
			FindBest(size, alignment, padding, previous, found);
			break;
		default:
			FATAL("Unknown BlobLoader optimization policy");
			break;
	}
}

void BlobLoader::FindBest (const size_t size, const size_t alignment, size_t & padding, Node *& previous, Node *& found)
{
	size_t smallestDiff = std::numeric_limits<size_t>::max();
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

void BlobLoader::Free (void * data)
{
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
	
	Coalescence(itPrev, free);
}

void BlobLoader::Reset ()
{
	memoryUsed = 0;
	memoryPeak = 0;
	
	Node * firstNode = (Node *) start;
	firstNode -> data.blockSize = bufferSize;
	firstNode -> next = nullptr;
	
	freeList.head = nullptr;
	freeList.Insert(nullptr, firstNode);
}