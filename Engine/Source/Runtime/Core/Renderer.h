#pragma once

#include "Mesh.h"
#include "Shader.h"

/**
 *
 * @class Renderer
 * @headerfile Renderer.h <Core/Renderer.h>
 * @author Seth Traman
 * @date August 2018
 *
 * @brief Simple OpenGL renderer designed to render a textured mesh
 *
 * @deprecated Renderer can be expected to be factored out in a near-future update.  This will be accompanied by several other rendering-related changes.
 *
 **/

class Renderer
{

public:

	Renderer ();
	Renderer (const Renderer & copy) = delete;
	~Renderer ();

	Renderer & operator= (const Renderer & copy) = delete;

	void Render (const Mesh & mesh, const Shader & shader) const;
};
