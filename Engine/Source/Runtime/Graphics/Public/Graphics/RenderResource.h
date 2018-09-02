#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	using ResourceHandle = uint16; ///< Max 65,535 indexable render resources

	struct VertexAttribute
	{
		uint32 elementCount; ///< Number of components (i.e. position has 3, {x y z})
		uint32 stride; ///< Distance between each appearance of this attribute
		uint32 offset; ///< Used internally, shouldn't be set
	};

	struct VertexArrayDescription
	{
		float * vertices; ///< A float array or similar containing vertex data to be uploaded and drawn
		uint32 verticesSize; ///< The number of elements / vertices in the vertex buffer

		uint32 * indices; ///< A uint32 array containing the indices into the vertices buffer to be drawn
		uint32 indicesSize; ///< The number of elements / indices in the index buffer

		VertexAttribute * vertexAttributes; ///< Array of vertex buffer attribute descriptions
		uint32 bufferDescCount; ///< Number of vertex attributes in the attribute buffer
	};
}
