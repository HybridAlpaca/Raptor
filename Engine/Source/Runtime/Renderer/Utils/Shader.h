#pragma once

#include <Core/Common/Required.h>

namespace Renderer::Utils
{

class Shader
{
	static uint16 boundShader;

public:

	Shader (cchar vertPath, cchar fragPath);
	Shader (const Shader & copy);
	~Shader ();
	
	void Destroy ();
	
	void Use ();
};

}