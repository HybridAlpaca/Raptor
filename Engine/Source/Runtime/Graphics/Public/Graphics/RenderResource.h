#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	template <uint32 T, uint32 U>
	struct GenericHandle
	{
		uint32 version: T;
		uint32 index: U;
	};

	using VertexArrayHandle = GenericHandle<16, 16>;
	using ShaderProgramHandle = GenericHandle<16, 16>;
}
