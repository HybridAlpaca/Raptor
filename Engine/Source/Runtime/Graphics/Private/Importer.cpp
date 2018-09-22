#include <Importer.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Graphics;

/**
 *
 * THIS
 *
 * IS
 *
 * NOT
 *
 * THREAD
 *
 * SAFE
 *
 **/

namespace
{
	Model model;
}

Importer::Importer (cchar directory)
: directory (directory)
{
	//
}

Importer::~Importer ()
{
	//
}

Model Importer::Load (cchar path)
{
	Assimp::Importer importer;
	const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene)
	{
		/// @todo Return error code
		return { };
	}

	ProcessNode(scene -> mRootNode, scene);

	return model;
}

void Importer::ProcessNode (aiNode * node, const aiScene * scene)
{
	// Find all meshes in this node
	for (uint32 i = 0; i < node -> mNumMeshes; ++i)
	{
		aiMesh * mesh = scene -> mMeshes[node -> mMeshes[i]];

		model.meshes[model.meshCount++] = ProcessMesh(mesh, scene);
	}

	// Recurse into all children nodes
	for (uint32 i = 0; i < node -> mNumChildren; ++i)
	{
		ProcessNode(node -> mChildren[i], scene);
	}
}

Mesh Importer::ProcessMesh (aiMesh * mesh, const aiScene * scene)
{
	Vertex * vertices = new Vertex [mesh -> mNumVertices];
	uint32 * indices = new uint32 [40960];
	uint32 indexCount = 0;

	for (uint32 i = 0; i < mesh -> mNumVertices; ++i)
	{
		vertices[i].position[0] = mesh -> mVertices[i].x;
		vertices[i].position[1] = mesh -> mVertices[i].y;
		vertices[i].position[2] = mesh -> mVertices[i].z;
	}

	for (uint32 i = 0; i < mesh -> mNumFaces; ++i)
	{
		aiFace face = mesh -> mFaces[i];

		for (uint32 j = 0; j < face.mNumIndices; ++j)
		{
			indices[indexCount++] = (face.mIndices[j]);
		}
	}

	return { vertices, indices };
}
