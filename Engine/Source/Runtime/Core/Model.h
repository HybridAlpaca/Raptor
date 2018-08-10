#pragma once

#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <string>

/**
 *
 * @class ModelLoader
 * @headerfile Model.h <Core/Model.h>
 * @author Seth Traman
 * @date August 2018
 *
 * @brief Used to load graphical models into the game from disk
 *
 * @deprecated ModelLoader is a very quick and sloppy class for dragging assets off disk.  This will be reimplemented and replaced by a dedicated resoure manager in a future update
 * @bug Doesn't free textures from memory upon model / mesh destruction
 * @bug Doesn't free model resources upon destruction
 * @warning ModelLoader is a ducking slob and doesn't clean up after itself.  Don't be like ModelLoader.  Be a good programmer and free your unused resources.
 *
 **/

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

	/// @param directory : The file path that the loader should look for models and textures in
	ModelLoader (const char * directory);

	/// Noncopyable
	ModelLoader (const ModelLoader & copy) = delete;

	/// Does nothing.  See warning for more details
	~ModelLoader ();

	/// Noncopyable
	ModelLoader & operator= (const ModelLoader & copy) = delete;

	/// @brief Loads a model from disk
	/// @param path : the location of the model file, relative to the loader's provided directory
	/// @return A standard vector of Mesh objects for which to be rendered
	std::vector<Mesh> Load (const char * path);
};
