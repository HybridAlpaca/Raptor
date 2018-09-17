#pragma once

#include <Raptor/Required.h>

namespace Graphics
{
	using RenderResource = uint16;

	enum class ShaderType
	{
		VERTEX,
		FRAGMENT
	};

	enum class BufferType
	{
		VERTEX,
		INDEX
	};

	struct BufferDescriptor
	{
		BufferType type;

		uint32 size;
	};

	struct Buffer
	{
		enum class Type
		{
			VERTEX,
			INDEX
		};

		RenderResource handle;

		Type type;

		uintptr size;
	};
}
