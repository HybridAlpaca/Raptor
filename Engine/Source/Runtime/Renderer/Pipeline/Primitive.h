#pragma once

#include <Core/Misc/Required.h>
#include <Renderer/Utils/Window.h>

namespace Renderer
{
namespace Pipeline
{

class PrimitiveRenderer
{

	Utils::WindowController * window;

public:

	PrimitiveRenderer (Utils::WindowController * window);
	
	~PrimitiveRenderer ();
	
	void Destroy ();
	
	void Simulate (uint16 vao);

};

}
}