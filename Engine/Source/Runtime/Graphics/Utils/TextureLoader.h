#pragma once

#include <Core/Common/Required.h>

#define STB_IMAGE_IMPLEMENTATION
#include <STBI/stb_image.h>
#include <GL/glew.h>

namespace Graphics::Utils
{

static const uint32 LoadTexture (cchar path)
{
	uint32 texture;
	glGenTextures(1, & texture);

	// load and generate the texture
	int32 width, height, channelCount;

	stbi_set_flip_vertically_on_load(true);
	uchar data = stbi_load(path, & width, & height, & channelCount, 0);

	if (data)
	{
		GLenum format = GL_RED;
		if (channelCount == 3)
		{
			format = GL_RGB;
		}
		else if (channelCount == 4)
		{
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, texture);
		// set the texture options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// apply image data
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);

		DEBUG("Successfuly loaded texture " << path);
	}
	else
	{
		DEBUG("Failed to load texture " << path);
	}

	return texture;
}

static void FreeTexture (uint32 * texture)
{
	glDeleteTextures(1, texture);
	DEBUG("Texture freed");
}

}
