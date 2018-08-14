#pragma once

namespace Graphics
{

template <unsigned int N1, unsigned int N2>
struct GenericHandle
{
	unsigned int generation : N1;
	unsigned int index : N2;
};

using VertexArrayHandle = GenericHandle<20, 12>;

}
