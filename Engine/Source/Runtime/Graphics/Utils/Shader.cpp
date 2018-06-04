#include <Core/Common/Required.h>
#include "Shader.h"

#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <string>

using Graphics::Utils::Shader;

Shader::Shader (cchar vertPath, cchar fragPath)
{
	std::string vertCode = ReadFile(vertPath);
	std::string fragCode = ReadFile(fragPath);
	
	Compile(vertCode.c_str(), fragCode.c_str());
}

Shader::~Shader ()
{
	Destroy();
}

void Shader::CheckErrors (const uint32 shader, ShaderType type)
{
	int success;
	char infoLog[1024];

	if (type != ShaderType::PROGRAM)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, & success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			DEBUG("Shader compilation error: " << infoLog);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, & success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			DEBUG("Program linking error: " << infoLog);
		}
	}
}

void Shader::Compile (cchar vertCode, cchar fragCode)
{
	uint32 vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, & vertCode, nullptr);
	glCompileShader(vertex);
	CheckErrors(vertex, ShaderType::VERTEX);
	
	uint32 fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, & fragCode, nullptr);
	glCompileShader(fragment);
	CheckErrors(fragment, ShaderType::FRAGMENT);
	
	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	CheckErrors(id, ShaderType::PROGRAM);
	
	glDetachShader(id, vertex);
	glDeleteShader(vertex);
	glDetachShader(id, fragment);
	glDeleteShader(fragment);
}

void Shader::Bind ()
{ glUseProgram(id); }

void Shader::Destroy ()
{
	glUseProgram(0);
	if (id)
	{
		glDeleteShader(id);
		id = 0;
	}
}

std::string Shader::ReadFile (cchar path)
{
	std::ifstream fileBuffer;
	std::stringstream dataBuffer;
	
	fileBuffer.open(path);
	if (fileBuffer.is_open())
	{
		dataBuffer << fileBuffer.rdbuf();
		fileBuffer.close();
		return dataBuffer.str();
	}
	
	DEBUG("Shader file " << path << " not found");
	return std::string("");
}

void Shader::Float (cchar name, float val) const
{ glUniform1f(glGetUniformLocation(id, name), val); }

void Shader::Int (cchar name, int32 val) const
{ glUniform1i(glGetUniformLocation(id, name), val); }