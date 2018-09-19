#pragma once

#include <Raptor/Required.h>

namespace Graphics
{
	using RenderResource = uint16;
	const RenderResource NullResource = 0;

	struct VertexAttribute
	{
		uint8 size;		  ///< Number of attrib components (i.e. position has 3, {x y z})
		uint8 stride;   ///< Byte offset between consecutive appearances of this attribute
		uint8 offset;   ///< Byte offset to first appearance of this attribute in the vertex buffer
	};

	enum class BufferType
	{
		VERTEX,
		INDEX
	};

	struct BufferDescriptor
	{
		/// The type of this buffer
		BufferType type;

		/// The size in bytes of the data stored in the buffer
		uint32 size;

		/// Additional data specific to each buffer type

		VertexAttribute * attribs;

		uint16 attribCount;
	};

	enum class ShaderType
	{
		VERTEX,
		FRAGMENT
	};
}
