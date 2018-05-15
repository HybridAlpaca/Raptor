#pragma once

#include <Core/Misc/Required.h>

#include <queue>
#include <unordered_map>

namespace Core
{
namespace Memory
{

/**

EXAMPLE USAGE

AssetManager manager(2048, "./lib/assets/");
Foo * theFoo = manager.LoadImmediate<>();

manager.Unload(theFoo);
manager.Unload(theBar);
// OR manager.UnloadAll();

**/

template <class Allocator>
class AssetManager
{

	Allocator & allocator;
	
	std::unordered_map<uint16, void *> assets;
	
	std::queue<uint16> errors;

public:

	// return codes for public methods
	enum class ErrCode
	{
		OK,
		FILE_NOT_EXIST,
		ASSET_NOT_LOADED,
		OUT_OF_MEMORY
	};

	AssetManager (size_t buffer_size);
	
	~AssetManager ();
	
	void Destroy ();
	
	ErrCode GetError ();
	
	template <typename AssetType>
	AssetType * LoadImmediate ();
	
	template <typename AssetType>
	void Unload (AssetType * asset);

};

}
}