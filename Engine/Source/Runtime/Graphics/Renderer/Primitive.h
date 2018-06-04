#pragma once

#include <Core/Common/Required.h>
#include <Graphics/Utils/Shader.h>

namespace Graphics::Renderer
{

class Primitive
{

	using Shader = Utils::Shader;

public:

	Primitive ();
	Primitive (const Primitive & copy) = delete;
	~Primitive ();
	
	Primitive & operator= (const Primitive & rhs) = delete;
	
	void Preprocess ();
	void Render (uint32 vao, const Shader & shader);
	
	void Destroy ();

};

}