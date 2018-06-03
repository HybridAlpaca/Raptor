#pragma once

#include <Core/Common/Required.h>

namespace Renderer::Utils
{

class Shader
{
	enum class ShaderType
	{
		VERTEX,
		GEOMETRY,
		FRAGMENT,
		PROGRAM
	};

	uint32 id;
	
	cchar ReadFile (cchar filePath);
	
	void Compile (cchar vertCode, cchar fragCode);
	
	void CheckErrors (const uint32 shader, ShaderType type);

public:

	Shader (cchar vertPath, cchar fragPath);
	Shader (const Shader & copy) = delete;
	~Shader ();
	
	Shader & operator= (const Shader & rhs) = delete;
	
	void Bind ();
	void Destroy ();
};

}