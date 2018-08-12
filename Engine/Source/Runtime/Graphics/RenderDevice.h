#pragma once

namespace Graphics
{

class RenderDevice
{
	// private data methods

public:

	RenderDevice ();
	RenderDevice (const RenderDevice & copy) = delete;
	~RenderDevice ();
	
	RenderDevice & operator= (const RenderDevice & rhs) = delete;
	
	void Draw ();
};

}
