#pragma once

#include <Core/Common/Required.h>

namespace Renderer::Utils
{

class Shader
{
	uint32 id;
	
	cchar ReadFile (cchar filePath);

public:

	Shader (cchar vertPath, cchar fragPath);
	Shader (const Shader & copy);
	~Shader ();
	
	void Destroy ();
	
	void Use ();
};

}