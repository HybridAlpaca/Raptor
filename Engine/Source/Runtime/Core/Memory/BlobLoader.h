#pragma once

#include <Core/Common/Required.h>
#include <Core/Containers/SLinkedList.h>

namespace Core
{
namespace Memory
{

enum class OptimizePolicy
{
	BEST,
	FIRST
};

class BlobLoader
{
	struct FreeHeader { size_t blockSize; };
	struct AllocHeader { size_t blockSize; char padding; };
	
	typedef Core::Containers::SinglyLinkedList<FreeHeader>::Node Node;
	
	OptimizePolicy policy;
	
	Core::Containers::SinglyLinkedList<FreeHeader> freeList;
	
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

	BlobLoader (size_t bufferSize, OptimizePolicy policy);
	
	BlobLoader (const BlobLoader & copy) = delete;
	
	~BlobLoader ();
	
	BlobLoader & operator= (const BlobLoader & copy) = delete;
	
	void * Alloc (const size_t size, const size_t alignment);
	
	void Free (void * data);
	
	void Destroy ();
	
	void Reset ();
};

}
}