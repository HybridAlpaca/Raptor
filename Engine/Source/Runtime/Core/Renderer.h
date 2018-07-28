#pragma once

#include "Mesh.h"
#include "Shader.h"

class Renderer
{

public:

	Renderer ();
	Renderer (const Renderer & copy) = delete;
	~Renderer ();
	
	Renderer & operator= (const Renderer & copy) = delete;
	
	void Render (const Mesh & mesh, const Shader & shader) const;
};
