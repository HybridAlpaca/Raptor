#include <Core/Misc/Required.h>
#include "Shader.h"

#include <fstream>
#include <sstream>
#include <string>

using Renderer::Utils::ShaderController;

uint8 ShaderController::boundShader = 0;

ShaderController::ShaderController ()
{
	//
}

ShaderController::~ShaderController ()
{
	Destroy();
}

void ShaderController::Destroy ()
{
	boundShader = 0;
}

cchar ShaderController::ReadFile (cchar file_name)
{
	std::ifstream fstream;
	std::stringstream sstream;
	
	fstream.open(file_name);
	if (fstream.is_open())
	{
		sstream << fstream.rdbuf();
		fstream.close();
		return std::string(sstream.str()).c_str();
	}
	else
	{
		DEBUG("Failed to open shader file");
	}
	
	return "";
}