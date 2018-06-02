#pragma once

#include <Core/Common/Required.h>

#include <unordered_map> // use this for shader caches

namespace Renderer::Utils
{

enum class ShaderType
{
	PROGRAM,
	VERTEX,
	FRAGMENT
};

class ShaderController
{
	typedef uint8 Shader; // handle to OpenGL shader

	static Shader boundShader;
	
	cchar directory;
	
	std::unordered_map<cchar, uint16> shaderCache;
	
	void CheckCompilerErrors (Shader shader, ShaderType type);

public:

	ShaderController (cchar directory);
	
	~ShaderController ();
	
	const Shader Compile (cchar shader_name);
	
	void Destroy ();
	
	void Free (Shader shader);
	
	cchar ReadFile (cchar file_name);
	
	void Use ();
};

}