#include "Shader.h"

#include <GL/glew.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

Shader::Shader (const char * vertPath, const char * fragPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		// open files
		vShaderFile.open(vertPath);
		fShaderFile.open(fragPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();		
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode   = vShaderStream.str();
		fragmentCode = fShaderStream.str();	
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char * vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, & vShaderCode, NULL);
	glCompileShader(vertex);
	// fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, & fShaderCode, NULL);
	glCompileShader(fragment);
	// shader Program
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);	
}

Shader::~Shader ()
{}

void Shader::Bind ()
{
	glUseProgram(ID);
}

void Shader::Bool (const char * name, bool val) const
{ glUniform1i(glGetUniformLocation(ID, name), (int) val); }

void Shader::Int (const char * name, int val) const
{ glUniform1i(glGetUniformLocation(ID, name), val); }

void Shader::Float (const char * name, float val) const
{ glUniform1f(glGetUniformLocation(ID, name), val); }

void Shader::Vec3 (const char * name, const glm::vec3 & val) const
{ glUniform3fv(glGetUniformLocation(ID, name), 1, & val[0]); }

void Shader::Mat3 (const char * name, const glm::mat3 & val) const
{ glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, & val[0][0]); }

void Shader::Mat4 (const char * name, const glm::mat4 & val) const
{ glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, & val[0][0]); }
