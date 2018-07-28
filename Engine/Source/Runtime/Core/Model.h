#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

class Model
{
	std::vector<Mesh> meshes;
	std::vector<Texture> textureCache;
	std::string directory;
	
	void LoadModel (const char * path);
	void ProcessNode (aiNode * node, const aiScene * scene);
	Mesh ProcessMesh (aiMesh * mesh, const aiScene * scene);
	
	std::vector<Texture> LoadTextures (aiMaterial * mat, aiTextureType type, TextureType typeName);
	
	unsigned int TextureFromFile (const char * path, std::string directory, bool gamma = true);

public:

	Model (const char * path);
	Model (const Model & copy) = delete;
	~Model ();
	
	Model & operator= (const Model & copy) = delete;
	
	void Draw (const Shader & shader) const;

};
