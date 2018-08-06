#pragma once

#include "RenderContext.h"

namespace GL
{

class GLRenderer
{
	RenderContext & ctx;

public:

	GLRenderer (RenderContext & context);
	GLRenderer (const GLRenderer & copy) = delete;
	~GLRenderer ();
	
	GLRenderer & operator= (const GLRenderer & rhs) = delete;
	
	void Render (const Mesh & mesh, const Shader & shader);
}

}
