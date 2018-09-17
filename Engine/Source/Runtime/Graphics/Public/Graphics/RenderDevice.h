#pragma once

#include <Raptor/Required.h>
#include "Resource.h"

namespace Graphics::RenderDevice
{
	void Init ();

	void Clear (float32 r, float32 g, float32 b, float32 a);

	RenderResource CreateShader (cchar code, ShaderType type);

	RenderResource CreateProgram (const RenderResource * shaders, uint16 shaderCount);

	RenderResource CreateVertexArray ();

	RenderResource CreateBuffer (RenderResource vertexArray, void * data, const BufferDescriptor & type);
}
