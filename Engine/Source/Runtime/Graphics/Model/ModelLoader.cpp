#include <Core/Common/Required.h>
#include <Graphics/Utils/Shader.h>
#include <Graphics/Utils/TextureLoader.h>
#include "ModelLoader.h"

#include <glm/glm.hpp>

#include <string>

using Graphics::Model::ModelLoader;
using Graphics::Utils::Shader;
using Graphics::Model::Mesh;
using Graphics::Model::Texture;
using Graphics::Model::TextureType;
using Graphics::Utils::LoadTexture;

ModelLoader::ModelLoader (cchar path)
{
	LoadModel(path);
}

ModelLoader::~ModelLoader ()
{
	// TODO
}

void ModelLoader::Draw (const Shader & shader)
{
	for (uint32 i = 0; i < meshes.size(); ++i)
	{
		meshes[i].Draw(shader);
	}
}

void ModelLoader::LoadModel (cchar path)
{
	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene -> mFlags & AI_SCENE_FLAGS_INCOMPLETE || ! scene -> mRootNode)
	{
		DEBUG("! ASSIMP error: " << import.GetErrorString());
		return;
	}

	std::string pathStr = path;
	directory = pathStr.substr(0, pathStr.find_last_of('/')).c_str();

	ProcessNode(scene -> mRootNode, scene);
}

std::vector<Texture> ModelLoader::LoadTextures (aiMaterial * mat, aiTextureType type, TextureType typeName)
{
	std::vector<Texture> textures;
	DEBUG("+ Load Model Textures");

	for (uint32 i = 0; i < mat -> GetTextureCount(type); ++i)
	{
		aiString str;
		mat -> GetTexture(type, i, & str);
		bool skip = false;
		for (uint32 j = 0; j < textureCache.size(); ++j)
		{
			if (std::strcmp(textureCache[j].path, str.C_Str()) == 0)
			{
				DEBUG("* Texture cache hit");
				textures.push_back(textureCache[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			// if texture hasn't been loaded already, load it
			Texture texture;
			std::string path = std::string(directory) + '/' + str.C_Str();
			texture.id = LoadTexture(path.c_str());
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textureCache.push_back(texture); // add to loaded textures
		}
	}

	DEBUG("- Load Model Textures");
	return textures;
}

void ModelLoader::ProcessNode (aiNode * node, const aiScene * scene)
{
	for (uint32 i = 0; i < node -> mNumMeshes; ++i)
	{
		aiMesh * mesh = scene -> mMeshes[node -> mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (uint32 i = 0; i < node -> mNumChildren; ++i)
	{
		ProcessNode (node -> mChildren[i], scene);
	}
}


Mesh ModelLoader::ProcessMesh (aiMesh * mesh, const aiScene * scene)
{
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<uint32> indices;
	std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	DEBUG("+ Vertex data extraction");
	for (uint32 i = 0; i < mesh -> mNumVertices; ++i)
	{
		Vertex vertex;
		glm::vec3 vector(0.0f, 0.0f, 0.0f); // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh -> mVertices[i].x;
		vector.y = mesh -> mVertices[i].y;
		vector.z = mesh -> mVertices[i].z;
		vertex.position = vector;

		// normals
		vector.x = mesh -> mNormals[i].x;
		vector.y = mesh -> mNormals[i].y;
		vector.z = mesh -> mNormals[i].z;
		vertex.normal = vector;

		// texture coordinates
		if (mesh -> mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec(0.0f, 0.0f);
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = vec;
		}
		else
		{
			vertex.texCoord = glm::vec2(0.0f, 0.0f);
		}
		// tangent
		vector = glm::vec3(0.0f, 0.0f, 0.0f);
		vector.x = mesh -> mTangents[i].x;
		vector.y = mesh -> mTangents[i].y;
		vector.z = mesh -> mTangents[i].z;
		vertex.tangent = vector;
		// bitangent
		vector.x = mesh -> mBitangents[i].x;
		vector.y = mesh -> mBitangents[i].y;
		vector.z = mesh -> mBitangents[i].z;
		vertex.bitangent = vector;

		vertices.push_back(vertex);
	}
	DEBUG("- Vertex data extraction");

	// now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	DEBUG("+ Face data extraction");
	for (uint32 i = 0; i < mesh -> mNumFaces; ++i)
	{
		aiFace face = mesh -> mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (uint32 j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}
	DEBUG("- Face data extraction");

	// process materials
	DEBUG("+ Material processing");
	aiMaterial * material = scene -> mMaterials[mesh -> mMaterialIndex];
	// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
	// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
	// Same applies to other texture as the following list summarizes:
	// diffuse: texture_diffuseN
	// specular: texture_specularN
	// normal: texture_normalN

	// 1. diffuse maps
	std::vector<Texture> diffuseMaps = LoadTextures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<Texture> specularMaps = LoadTextures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = LoadTextures(material, aiTextureType_HEIGHT, TextureType::NORMAL);
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = LoadTextures(material, aiTextureType_AMBIENT, TextureType::HEIGHT);
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
	DEBUG("- Material processing");

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures);
}
