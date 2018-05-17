#pragma once

#include <Core/Misc/Required.h>

#include <fstream>
#include <unordered_map> // use this for shader caches

namespace Renderer
{
namespace Utils
{

class ShaderController
{

	static uint16 boundShader;
	
	std::ifstream VertexFile;
	std::ifstream FragmentFile;
	
	string vertexCode;
	string fragmentCode;
	
	void CheckCompilerErrors (uint16 shader, ShaderType type);
	
	void ReadFile (cchar file_name);

public:

	enum class ShaderType
	{
		PROGRAM,
		VERTEX,
		FRAGMENT
	};

	ShaderController ();
	
	~ShaderController ();
	
	uint16 Compile ();
	
	void Destroy ();
	
	void Use ();

};

}
}