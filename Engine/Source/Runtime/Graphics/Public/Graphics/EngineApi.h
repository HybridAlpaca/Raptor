#pragma once

#include "PluginsApi.h"
#include "RenderDevice.h"

namespace Graphics::Api
{
	class v0 : public GraphicsApi
	{
		uint16 CreateShader (cchar vertexCode, cchar fragmentCode) override
		{
			RenderResource shaders [] =
			{
				RenderDevice::AllocateShader(vertexCode,   ShaderType::VERTEX),
				RenderDevice::AllocateShader(fragmentCode, ShaderType::FRAGMENT)
			};

			RenderResource program = RenderDevice::AllocateShaderProgram(shaders, 2);

			RenderDevice::DestroyShader(shaders[0]);
			RenderDevice::DestroyShader(shaders[1]);

			return program;
		}

		void DestroyShader (uint16 shader) override
		{
			RenderDevice::DestroyShaderProgram(shader);
		}

		uint16 CreateVertexArray () override
		{
			return RenderDevice::AllocateVertexArray();
		}

		void DestroyVertexArray (uint16 vertexArray) override
		{
			RenderDevice::DestroyVertexArray(vertexArray);
		}

		uint16 CreateBuffer (uint16 vertexArray, void * data, uint16 type, uintptr size, uint8 * attribs, uint16 attribCount) override
		{
			BufferType bufferType = (type == 0) ? BufferType::VERTEX : BufferType::INDEX;

			VertexAttribute attributes [attribCount];

			uint32 e = 0;

			for (uint16 i = 0; i < attribCount; ++i)
			{
				attributes[i] = { attribs[e++], attribs[e++], attribs[e++] };
			}

			BufferDescriptor desc = { bufferType, size, attributes, attribCount };

			return RenderDevice::AllocateBuffer(vertexArray, data, desc);
		}

		void DestroyBuffer (uint16 buffer) override
		{
			RenderDevice::DestroyBuffer(buffer);
		}

		void DrawIndexed (uint16 vertexArray, uint16 shader, uint16 indexCount)
		{
			RenderDevice::DrawIndexed(vertexArray, shader, indexCount, 0);
		}

		void Clear (float32 color [4]) override
		{
			RenderDevice::Clear(color);
		}
	};
}
