#pragma once

#include <Core/Misc/Required.h>

#include <unordered_map>

namespace Core
{
namespace Memory
{

template <class Allocator>
class AssetManager
{

	typedef uint16 AssetHandle;

	Allocator & allocator;
	
	std::unordered_map<uint16, void *> assets;

public:

	enum class ErrCode
	{
		OK,
		NOT_LOADED,
		OUT_OF_MEMORY
	};

	AssetManager (size_t buffer_size, cchar disk_directory);
	
	~AssetManager ();
	
	void Destroy ();
	
	ErrCode LoadFromDisk (cchar path);
	
	ErrCode Unload (uint16 handle);

};

}
}