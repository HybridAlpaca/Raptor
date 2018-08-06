#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <STBI/stb_image.h>

#include <string>
#include <iostream>

ModelLoader::ModelLoader (const char * directory)
: directory (directory)
{}

ModelLoader::~ModelLoader ()
{}

std::vector<Mesh> ModelLoader::Load (const char * path)
{
	meshes.clear();
	LoadModel(path);
	return meshes;
}

void ModelLoader::LoadModel (const char * path)
{
	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(directory + '/' + path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes | aiProcess_ImproveCacheLocality);

	if (!scene || scene -> mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene -> mRootNode) 
	{
		std::cout << "Scene failed to load." << "\n";
		return;
	}
	
	std::string pathStr = path;
	localDir = pathStr.substr(0, pathStr.find_last_of('/'));

	ProcessNode(scene -> mRootNode, scene);
}

void ModelLoader::ProcessNode (aiNode * node, const aiScene * scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node -> mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh * mesh = scene -> mMeshes[node -> mMeshes[i]];
		meshes.push_back(ProcessMesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node -> mNumChildren; i++)
	{
		ProcessNode(node -> mChildren[i], scene);
	}
}

Mesh ModelLoader::ProcessMesh (aiMesh * mesh, const aiScene * scene)
{
	Mesh newMesh;
	
	// data to fill
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
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
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh -> mTextureCoords[0][i].x; 
			vec.y = mesh -> mTextureCoords[0][i].y;
			vertex.texcoords = vec;
		}
		else
			vertex.texcoords = glm::vec2(0.0f, 0.0f);
		// tangent
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
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for(unsigned int i = 0; i < mesh -> mNumFaces; i++)
	{
		aiFace face = mesh -> mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
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

	newMesh.vertices = vertices;
	newMesh.indexCount = indices.size();
	newMesh.textures = textures;
	
	glGenVertexArrays(1, & newMesh.VAO);
	glGenBuffers(1, & newMesh.VBO);
	glGenBuffers(1, & newMesh.EBO);

	glBindVertexArray(newMesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, newMesh.VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), & vertices[0], GL_STATIC_DRAW);  

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newMesh.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), & indices[0], GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) 0);
	// vertex normals
	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texcoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, bitangent));

	glBindVertexArray(0);
	
	return newMesh;
}

std::vector<Texture> ModelLoader::LoadTextures (aiMaterial * mat, aiTextureType type, TextureType typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat -> GetTextureCount(type); i++)
	{
		aiString str;
		mat -> GetTexture(type, i, & str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textureCache.size(); j++)
		{
			if (std::strcmp(textureCache[j].path, str.C_Str()) == 0)
			{
				std::cout << textureCache[j].path << "\n";
				textures.push_back(textureCache[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			bool gamma = true;
			if (typeName != TextureType::DIFFUSE) gamma = false;
			texture.id = TextureFromFile(str.C_Str(), gamma);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			//textureCache.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

unsigned int ModelLoader::TextureFromFile (const char * path, bool gamma)
{
	std::string filename = directory + '/' + localDir + '/' + std::string(path);
	unsigned int textureID;
	glGenTextures(1, & textureID);

	int width, height, channelCount;
	unsigned char * data = stbi_load(filename.c_str(), & width, & height, & channelCount, 0);
	if (data)
	{
		GLenum format = GL_RED;
		GLenum sformat = GL_RED;
		if (channelCount == 3)
		{
			format = GL_RGB;
			if (gamma) sformat = GL_SRGB;
			else sformat = format;
		}
		else if (channelCount == 4)
		{
			format = GL_RGBA;
			if (gamma) sformat = GL_SRGB_ALPHA;
			else sformat = format;
		}
		
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, sformat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load" << "\n";
		stbi_image_free(data);
	}

	return textureID;
}
