#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

class ModelLoader
{
	std::vector<Mesh> meshes;
	std::vector<Texture> textureCache;
	std::string directory;
	std::string localDir;
	
	void LoadModel (const char * path);
	void ProcessNode (aiNode * node, const aiScene * scene);
	Mesh ProcessMesh (aiMesh * mesh, const aiScene * scene);
	
	std::vector<Texture> LoadTextures (aiMaterial * mat, aiTextureType type, TextureType typeName);
	
	unsigned int TextureFromFile (const char * path, bool gamma = true);

public:

	ModelLoader (const char * directory);
	ModelLoader (const ModelLoader & copy) = delete;
	~ModelLoader ();
	
	ModelLoader & operator= (const ModelLoader & copy) = delete;
	
	std::vector<Mesh> Load (const char * path);
};
