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

		/// Implicit type conversion overload to return id
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
		uint8 offset = 0; ///< Byte offset to first appearance of this attribute
	};

	struct VertexFormat
	{
		/// Max attributes per vertex
		static const uint8 MAX_ATTRIBUTES = 255;

		enum class Type : uint8
		{
			VERTEX, ///< Specifies a vertex buffer
			INDEX		///< Specifies an index / element buffer
		};

		/// Vertex attribute buffer
		VertexAttribute attributes[MAX_ATTRIBUTES];

		uint32 verticesSize;
		uint32 indicesSize;

		/// The number of vertex attributes in the format
		uint32 attributeCount = 0;

		/// The type of this buffer
		Type type;

		/// Add an attribute to this description
		inline VertexFormat & AddAttribute (const VertexAttribute & attrib)
		{
			attributes[attributeCount++] = attrib;

			// Return dereferenced this to allow method chaining
			return (* this);
		}

		inline void End ()
		{
			uint32 attribStride = 0;

			for (uint32 i = 0; i < attributeCount; ++i)
			{
				attribStride += attributes[i].size;

				// Don't calculate offset if this is the first attribute
				if (i == 0) { continue; }

				if (!attributes[i].offset)
				{
					// If this attribute doesn't have a starting offset, assign one based on previous attributes
					attributes[i].offset = attributes[i - 1].offset + attributes[i - 1].size;
				}
			}

			for (uint32 i = 0; i < attributeCount; ++i)
			{
				if (!attributes[i].stride)
				{
					attributes[i].stride = attribStride;
				}
			}
		}
	};
}
