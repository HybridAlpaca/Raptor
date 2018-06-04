#include <Core/Common/Required.h>
#include "Primitive.h"

using Graphics::Renderer::Primitive;

Primitive::Primitive ()
{
	
}

Primitive::~Primitive ()
{
	Destroy ();
}

void Primitive::Destroy ()
{ /* TODO */ }

void Primitive::Render (uint32 vao, const Shader & shader)
{
	
}