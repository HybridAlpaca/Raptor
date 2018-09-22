#pragma once

#include <Raptor/Required.h>

class aiNode;
class aiScene;

namespace Graphics
{
	class Importer
	{
		cchar directory;

		void ProcessNode (aiNode * node, const aiScene * scene);

	public:

		Importer (cchar directory);
		Importer (const Importer & copy) = delete;
		~Importer ();

		Importer & operator= (const Importer & rhs) = delete;

		void Load (cchar path);
	};
}
