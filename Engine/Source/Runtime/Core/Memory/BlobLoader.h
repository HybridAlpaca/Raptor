#pragma once

#include <Core/Common/Required.h>

namespace Core
{
namespace Memory
{

class BlobLoader
{
	cchar basePath;
	
	size_t bufferSize;

	uint16 memoryUsed;
	uint16 memoryPeak;

	void * start = nullptr;
	void * current = nullptr;

public:

	BlobLoader (size_t bufferSize, cchar basePath);
	
	~BlobLoader ();
	
	void * Alloc (size_t size, size_t alignment);
	
	template <typename T>
	T * Alloc ();
	
	void Free (void * data);
	
	void LoadDisk ();
	
	void Destroy ();
};

}
}