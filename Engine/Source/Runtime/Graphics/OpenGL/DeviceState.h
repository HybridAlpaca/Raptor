#pragma once

#include "../Constants.h"

#include <GL/glew.h>

namespace Graphics::Backend::GL
{

struct DeviceState
{
	GLuint boundVAO = 0;

	GLuint VAOList [MAX_RENDER_RESOURCES];

	GLuint glVersionMajor = 1;
	GLuint glVersionMinor = 0;
	GLuint glVersionPatch = 0;
};

}
