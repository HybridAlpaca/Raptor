#pragma once

#include <Core/Common/Required.h>

namespace Core
{
namespace Memory
{

class AssetManager
{

	cchar directory;

	void * heap;

public:

	AssetManager (size_t bufferSize, cchar directory = "./");
	
	/// Disable copy constructor
	AssetManager (const AssetManager & copyParent) = delete;
	
	~AssetManager ();
	
	/// Disable move constructor
	AssetManager & operator= (const AssetManager & rhs) = delete;
	
	/// ::Allocate(size_t, size_t)
	/// Allows the dev to define the exact size
	/// and alignment of the buffer being allocated.
	/// Typical usage will involve sizeof() and alignof()
	/// being passed into the first and second args,
	/// respectively.
	void * Allocate (size_t bytes, size_t alignment);
	
	/// ::Allocate<Type>()
	/// Allows the dev to specify a type, and the
	/// manager will return a pointer to that type
	template <typename Type>
	Type * Allocate ();
	
	/// ::Allocate<Type>(uint16)
	/// Same as ::Allocate<Type>, but returns a
	/// pointer to an array of Type pointers with
	/// a designated array size
	template <typename Type>
	Type ** Allocate (uint16 arraySize);
	
	/// Destroys the AssetManager instance itself.
	/// It is ::Destroy's responsability to free
	/// any resources that were not previously
	/// deallocated and return system memory to its
	/// original state.  Is also called in d'tor.
	void Destroy ();
	
	/// Free data alloc'd by ::Allocate(size_t, size_t)
	/// as a void pointer.  In the case that this
	/// pointer is null, ::Free(nullptr_t) will be called.
	void Free (void * data);
	
	/// Used in the case that ::Free(void *) was
	/// passed a null pointer.  In the case that
	/// this happens, a friendly (non-fatal) warning
	/// should be given.
	void Free (nullptr_t data);
	
	/// Free data alloc'd via ::Allocate<Type>
	template <typename Type>
	void Free (Type * type);
	
	/// Free data allocated as an array, likely via
	/// ::Allocate<Type>(uint16)
	template <typename Type>
	void Free (Type ** type);
	
	/// Read data from a plain text file and return
	/// a char array pointer containing the raw data.
	/// Data allocated in this way should be freed
	/// via ::Free<Type>(Type **).
	cchar ReadTextFile (cchar fileName);
	
	/// Similar in use and function to
	/// ::ReadTextFile(cchar), but this time read a
	/// binary file and load it into memory.
	cchar ReadBinaryFile (cchar fileName);
};

}
}