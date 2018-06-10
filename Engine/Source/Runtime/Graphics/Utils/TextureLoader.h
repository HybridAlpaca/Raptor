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
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int32 width, height, nrChannels;
	uchar data = stbi_load(path, & width, & height, & nrChannels, 0);
	if (data)
	{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			DEBUG("Successfuly loaded texture " << path);
	}
	else
	{
			DEBUG("Failed to load texture " << path);
	}
	stbi_image_free(data);

	return texture;
}

static void FreeTexture (uint32 * texture)
{
	glDeleteTextures(1, texture);
	DEBUG("Texture freed");
}

}
