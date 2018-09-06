#pragma once

#include <Raptor/Required.h>

namespace Graphics
{
	struct RenderResource
	{
		using ID = uint16; ///< 16 Bits per handle
		static const ID NULL_ID = 0; /// A value of zero is reserved as an 'invalid' handle

		ID id = NULL_ID; /// The handle value of the resource
		ID version = 0; /// The generation of the resource.  Used to check for stale handles

		/// Turn this into a null handle
		inline void Invalidate () { id = NULL_ID; }

		/// Check for validity of resource
		inline bool Valid () const { return (id == NULL_ID); }

		inline operator uint16 () const { return id; }

		/// @return True if the two resources point to the same resource, false otherwise
		inline bool operator== (const RenderResource & rhs) const
		{
			return (rhs.id == id) && (rhs.version == version);
		}

		/// @return True if two resources point to different resources, false otherwise
		inline bool operator!= (const RenderResource & rhs) const
		{
			return (rhs.id != id) && (rhs.version != version);
		}

		/// @return True if refers to the same resource as the other and this is older, false otherwise
		inline bool operator< (const RenderResource & rhs) const
		{
			return (id == rhs.id) ? (version < rhs.version) : false;
		}

		/// @return True if refers to the same resource as the other and this is newer, false otherwise
		inline bool operator > (const RenderResource & rhs) const
		{
			return (id == rhs.id) ? (version > rhs.version) : false;
		}
	};

	// tests
	static_assert(sizeof(RenderResource) == (32 / 8), "RenderResource should take up 32 bits");

	struct VertexAttribute
	{
		uint8 size;		///< Number of components (i.e. position has 3, {x y z})
		uint8 stride; ///< Byte offset between consecutive appearances of this attribute
		uint8 offset; ///< Byte offset to first appearance of this attribute
	};

	struct VertexArrayDescription
	{
		VertexAttribute * vertexAttributes; ///< Array of vertex buffer attribute descriptions

		uint32 verticesSize; ///< The number of elements / vertices in the vertex buffer
		uint32 indicesSize; ///< The number of elements / indices in the index buffer

		uint8 bufferDescCount; ///< Number of vertex attributes in the attribute buffer
	};
}
