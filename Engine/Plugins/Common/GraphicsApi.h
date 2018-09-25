#pragma once

#include <Raptor/Required.h>

const int GRAPHICS_API = 1;

/**
 *
 * @class GraphicsApi
 * @author Seth Traman
 * @brief Abstract class describig the methods a graphics API is expected to have
 *
 **/
class GraphicsApi
{

public:

	virtual ~GraphicsApi () {}

	virtual uint16 CreateShader (cchar vertexCode, cchar fragmentCode) = 0;
	virtual void DestroyShader (uint16 shader) = 0;

	virtual uint16 CreateVertexArray () = 0;
	virtual void DestroyVertexArray (uint16 vertexArray) = 0;

	virtual uint16 CreateBuffer (uint16 vertexArray, void * data, uint16 type, uintptr size, uint8 * attribs, uint16 attribCount) = 0;
	virtual void DestroyBuffer (uint16 buffer) = 0;

	virtual void DrawIndexed (uint16 vertexArray, uint16 shader, uint16 indexCount) = 0;

	//

	virtual void Clear (float32 color [4]) = 0;
};
