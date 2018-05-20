#include <Core/Common/Required.h>
#include "Shader.h"

#include <fstream>
#include <sstream>
#include <string>

using Renderer::Utils::ShaderController;

uint8 ShaderController::boundShader = 0;

ShaderController::ShaderController (cchar directory)
: directory(directory)
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