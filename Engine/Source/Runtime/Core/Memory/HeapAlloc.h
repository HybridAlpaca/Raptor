#pragma once

#include <Core/Common/Required.h>
#include <Core/Containers/SLinkedList.h>

namespace Core::Memory
{

enum class OptimizePolicy
{
	BEST,
	FIRST
};

class HeapAllocator
{
	struct FreeHeader { size_t blockSize; };
	struct AllocHeader { size_t blockSize; char padding; };
	
	using FreeList = Core::Containers::SinglyLinkedList<FreeHeader>;
	using Node = FreeList::Node;
	
	OptimizePolicy policy;
	
	FreeList freeList;
	
	size_t bufferSize;
	size_t memoryUsed;
	size_t memoryPeak;

	void * start = nullptr;
	void * current = nullptr;
	
	void Coalescence (Node * prevBlock, Node * freeBlock);
	
	void Find (const size_t size, const size_t alignment, size_t & padding, Node *& previous, Node *& found);
	void FindBest (const size_t size, const size_t alignment, size_t & padding, Node *& previous, Node *& found);
	void FindFirst (const size_t size, const size_t alignment, size_t & padding, Node *& previous, Node *& found);

public:

	HeapAllocator (size_t bufferSize, OptimizePolicy policy);
	HeapAllocator (const HeapAllocator & copy) = delete;
	
	~HeapAllocator ();
	
	HeapAllocator & operator= (const HeapAllocator & copy) = delete;
	
	void * Alloc (const size_t size, const size_t alignment);
	
	void Free (void * data);
	
	void Destroy ();
	
	void Reset ();
};

}