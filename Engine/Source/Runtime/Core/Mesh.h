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

/**
 *
 * @struct Mesh
 * @headerfile Mesh.h <Core/Mesh.h>
 *
 * @brief Simple mesh structure containing all data required to render a physial 3D object
 *
 * @todo Get rid of OpenGL-specific data and abstract this over the new rendering engine.  At most, this should contain an index or pointer to a rendering resource; everything else should be library agnostic
 *
 **/

struct Mesh
{
	std::vector<Vertex> vertices;		///< List of all vertices in a mesh
	std::vector<Texture> textures;	///< List of all textures in a mesh

	unsigned int VAO;								///< Vertex array object (OpenGL)
	unsigned int VBO;								///< Vertex buffer object (OpenGL)
	unsigned int EBO;								///< Element (index) buffer object (OpenGL)

	unsigned int indexCount;				///< Number of indices in mesh, if any
};
