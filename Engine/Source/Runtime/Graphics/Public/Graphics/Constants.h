#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	struct VertexAttribute
	{
		uint32 elementCount; ///< Number of components (i.e. position has 3, {x y z})
		uint32 stride; ///< Distance between each appearance of this attribute
		uint32 offset;
	};

	struct VertexArrayDescription
	{
		float * vertices; ///< A float array or similar containing data to be uploaded and drawn
		uint32 verticesSize; ///< The number of elements / vertices in the data buffer

		uint32 * indices;
		uint32 indicesSize;

		VertexAttribute * vertexAttributes; ///< Array of vertex buffer attribute descriptions
		uint32 bufferDescCount; ///< Number of vertex attributes in the attribute buffer
	};

	using ResourceHandle = uint32;
}
