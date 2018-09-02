#pragma once

#include <Core/Common/Required.h>

namespace Graphics
{
	/// @deprecated Use RenderResource instead
	using ResourceHandle = uint16;

	struct RenderResource
	{
		using ID = uint16;
		static const ID NULL_ID = 0;

		ID id = NULL_ID;

		inline void Invalidate () { id = NULL_ID; }
		inline bool Valid () const { return (id == NULL_ID); }

		inline bool operator== (const RenderResource & rhs) { return (rhs.id == id); }
		inline bool operator!= (const RenderResource & rhs) { return (rhs.id != id); }
	};

	struct VertexDescriptor
	{
		static constexpr uint8 MAX_VERTEX_ATTRIBS = 255;

		struct Attribute
		{
			uint32 size;
			uint32 stride;
			uint32 offset;

			bool normalized;
		};

		Attribute attribs [MAX_VERTEX_ATTRIBS];

		void Begin ();
		void Add (uint32 size, uint32 stride, uint32 offset, bool normalized);
		void End ();
	};

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
