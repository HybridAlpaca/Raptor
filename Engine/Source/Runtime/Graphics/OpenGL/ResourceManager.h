#pragma once

#include "../RenderResource.h"

namespace Graphics::Backend
{

VertexArrayHandle CreateVertexArray ();
void DestroyVertexArray (VertexArrayHandle vertexArray);

}
