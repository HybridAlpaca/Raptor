#pragma once

#include <Core/Common/Required.h>
#include <Graphics/Utils/Shader.h>
#include "Geometry.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>

namespace Graphics::Model
{

class ModelLoader
{
	std::vector<Mesh> meshes;
	std::vector<Texture> textureCache;

	cchar directory;

	std::vector<Texture> LoadTextures (aiMaterial * mat, aiTextureType type, TextureType typeName);

	void LoadModel(cchar path);
	Mesh ProcessMesh(aiMesh * mesh, const aiScene * scene);
	void ProcessNode(aiNode * node, const aiScene * scene);

public:

	ModelLoader (cchar path);
	ModelLoader (const ModelLoader & copy) = delete;
	~ModelLoader ();

	ModelLoader & operator= (const ModelLoader & rhs) = delete;

	void Draw (const Utils::Shader & shader);
};

}
