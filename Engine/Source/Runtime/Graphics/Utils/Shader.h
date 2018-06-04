#pragma once

#include <Core/Common/Required.h>

#include <string>

namespace Graphics::Utils
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
	
	std::string ReadFile (cchar path);
	
	void Compile (cchar vertCode, cchar fragCode);
	
	void CheckErrors (const uint32 shader, ShaderType type);

public:

	Shader (cchar vertPath, cchar fragPath);
	Shader (const Shader & copy) = delete;
	~Shader ();
	
	Shader & operator= (const Shader & rhs) = delete;
	
	void Bind ();
	void Destroy ();
	
	void Float (cchar name, float val) const;
	void Int (cchar name, int32 val) const;
};

}