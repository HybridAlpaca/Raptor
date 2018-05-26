#pragma once

#include <Core/Common/Required.h>

namespace Core
{
namespace Memory
{

template <size_t size, typename Type>
class Cache
{

	Type cache[size];

public:
	
	Cache ();
	
	~Cache ();
	
	void Destroy ();
	
	bool Has (Type const & value) const;
	
	// returns true if operation was successful
	bool Insert (Type & value);
	
	// returns true if operation was successful
	bool Remove (Type & value);
};

}
}

/*

Cache<256, Entity *> cache;
BlobLoader loader(4096);

Entity * skb = loader.Alloc<Entity>();
cache.Insert(skb);

// do stuff with skelebones

cache.Remove(skb);
loader.Free<Entity>(skb);

// loop through cache and remove pointers you forgot to free

//////// ALTERNATE, WITH ASSET MANAGER

AssetManager<> am();

Entity * skb = am.Alloc<Entity>();

// do stuff with skelebones

am.Free<Entity>();

*/