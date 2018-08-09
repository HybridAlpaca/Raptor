#pragma once

#include "Shader.h"

#include <glm/glm.hpp>

#include <vector>

/**
 *
 * @struct Vertex
 * @headerfile Mesh.h <Core/Mesh.h> 
 * 
 * @brief Contains data on how each vertex is to be uploaded to the GPU
 * @todo Factor this class out, somehow support a more configurable vertex layout with the upcoming rendering engine?
 * 
 **/

struct Vertex
{
	glm::vec3 position;		///< Local position
	glm::vec3 normal;			///< Normals
	glm::vec2 texcoords;	///< Texture coordinates
	glm::vec3 tangent;		///< Tangent
	glm::vec3 bitangent;	///< Bitangent
};

/**
 *
 * @enum TextureType
 * @headerfile Mesh.h <Core/Mesh.h> 
 * 
 * @brief Identifies the various BSDF texture types supported by the rendering engine
 * 
 **/

enum class TextureType
{
	DIFFUSE,	///< Color map
	SPECULAR,	///< Shininess map
	NORMAL,		///< Reflectivity map
	HEIGHT		///< Bump / Displacement map
};

/**
 * 
 * @struct Texture
 * @headerfile Mesh.h <Core/Mesh.h>
 * 
 * @brief Weak abstraction over OpenGL texture resource
 * 
 **/

struct Texture
{
	unsigned int id;		///< OpenGL texture ID
	TextureType type;		///< Type of BSDF texture
	const char * path;	///< Path to this texture (for caching purposes)
};

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;
	
	unsigned int VAO, VBO, EBO;
	unsigned int indexCount;
};
