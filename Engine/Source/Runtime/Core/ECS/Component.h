#pragma once

#include <Core/Common/Required.h>

namespace Core::ECS
{

struct BaseComponent
{
	void * entity;
	static uint32 internalID;
};

template <class T>
struct Component : BaseComponent
{
	static const uint32 ID;
	static const size_t SIZE;
};

template <class T>
const uint32 Component<T>::ID(++BaseComponent::internalID);

template <class T>
const size_t Component<T>::SIZE(sizeof(T));

struct FooComponent : Component<FooComponent>
{
	float x;
	float y;
	float z;
};

struct BarComponent : Component<BarComponent>
{
	uint16 a;
	uint16 b;
	uint16 c;
};

}