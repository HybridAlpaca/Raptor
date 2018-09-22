#include <Importer.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Graphics;

Importer::Importer (cchar directory)
: directory (directory)
{
	//
}

Importer::~Importer ()
{
	//
}

void Importer::Load (cchar path)
{
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene)
	{
		/// @todo Return error code
		return;
	}

	ProcessNode(scene -> mRootNode, scene);
}

void Importer::ProcessNode (aiNode * node, const aiScene * scene)
{
	// Find all meshes in this node
	for (uint32 i = 0; i < node -> mNumMeshes; ++i)
	{
		aiMesh * mesh = scene -> mMeshes[node -> mMeshes[i]];
		(void) mesh;
	}

	// Recurse into all children nodes
	for (uint32 i = 0; i < node -> mNumChildren; ++i)
	{
		ProcessNode(node -> mChildren[i], scene);
	}
}
