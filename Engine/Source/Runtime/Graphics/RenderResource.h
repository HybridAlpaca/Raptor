#pragma once

namespace Graphics
{

struct RenderResource
{
	enum RenderResourceType : char
	{
		TEXTURE,
		RENDER_TARGET,
		VERTEX_STREAM,
		ELEMENT_STREAM,
		RAW_BUFFER,
		SHADER
	};

	unsigned int handle;
};

}
