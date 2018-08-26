#pragma once

#include "../Constants.h"

#include <GL/glew.h>

namespace Graphics::Backend::GL
{

struct DeviceState
{
	/// The currently bound Vertex Array Object
	GLuint boundVAO = 0;

	GLuint VAOList [MAX_RENDER_RESOURCES];

	GLuint glVersionMajor = 1; ///< V X.0.0
	GLuint glVersionMinor = 0; ///< V 0.X.0
	GLuint glVersionPatch = 0; ///< V 0.0.X
};

}
