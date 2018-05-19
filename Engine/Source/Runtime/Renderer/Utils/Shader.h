#pragma once

#include <Core/Misc/Required.h>

#include <unordered_map> // use this for shader caches

namespace Renderer
{
namespace Utils
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
	
	std::unordered_map<cchar, uint16> shaderCache;
	
	void CheckCompilerErrors (Shader shader, ShaderType type);
	
	cchar ReadFile (cchar file_name);

public:

	ShaderController ();
	
	~ShaderController ();
	
	const Shader Compile (cchar shader_name);
	
	void Destroy ();
	
	void Free (Shader shader);
	
	void Use ();
};

}
}