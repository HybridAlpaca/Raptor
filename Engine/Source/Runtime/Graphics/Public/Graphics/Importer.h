#pragma once

#include <Raptor/Required.h>

class aiNode;
class aiMesh;
class aiScene;

namespace Graphics
{
	struct Vertex
	{
		float32 position [3];
	};

	struct Mesh
	{
		Vertex * vertices;
		uint32 * indices;
	};

	struct Model
	{
		Mesh meshes [255];
		uint8 meshCount = 0;
	};

	class Importer
	{

		cchar directory;

		void ProcessNode (aiNode * node, const aiScene * scene);
		Mesh ProcessMesh (aiMesh * mesh, const aiScene * scene);

	public:

		Importer (cchar directory);
		Importer (const Importer & copy) = delete;
		~Importer ();

		Importer & operator= (const Importer & rhs) = delete;

		Model Load (cchar path);
	};
}
