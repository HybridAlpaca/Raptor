#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	enum class ShaderType
	{
		VERTEX,
		GEOMETRY,
		TESSCONTROL,
		TESSEVAL,
		FRAGMENT,
		COMPUTE
	};

	struct VertexBufferDescription
	{
		uint32 slot;
		uint32 elementCount;
		uint32 offset;
	};

	struct VertexArrayDescription
	{
		float * data;
		uint32 size;

		VertexBufferDescription * vertexBufferDesc;
		uint32 bufferDescCount;
	};

	using ResourceHandle = uint32;
}
