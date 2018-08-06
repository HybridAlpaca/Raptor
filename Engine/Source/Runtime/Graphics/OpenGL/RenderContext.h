#pragma once

#include "Constants.h"

#include <glm/glm.hpp>

#include <vector>

namespace GL
{
	
struct DrawCommand
{
	BlendFunc sourceBlend        	 = BlendFunc::NONE;
	BlendFunc destBlend            = BlendFunc::NONE;
	DrawFunc depthFunc             = DrawFunc::ALWAYS;
	DrawFunc stencilFunc           = DrawFunc::ALWAYS;
	FaceCulling faceCulling        = FaceCulling::NONE;
	PrimitiveType primitiveType    = PrimitiveType::TRIANGLES;
	StencilOp stencilFail          = StencilOp::KEEP;
	StencilOp stencilPassDepthFail = StencilOp::KEEP;
	StencilOp stencilPass          = StencilOp::KEEP;
	
	unsigned int stencilTestMask   = 0;
	unsigned int stencilWriteMask  = 0;
	int stencilComparisonVal       = 0;
	
	bool shouldWriteDepth          = true;
	bool useStencilTest            = false;
};
	
class RenderContext
{
	std::vector<unsigned int> FBOList;
	std::vector<unsigned int> VAOList;
	std::vector<unsigned int> ShaderList;
	
	unsigned int boundFBO    = 0;
	unsigned int boundVAO    = 0;
	unsigned int boundShader = 0;
	
	void BindFBO (unsigned int FBO);
	void BindVAO (unsigned int VAO);
	void BindShader (unsigned int shader);
	
public:
	
	RenderContext ();
	RenderContext (const RenderContext & copy) = delete;
	~RenderContext ();
	
	RenderContext & operator= (const RenderContext & rhs) = delete;
	
	void Clear (unsigned int FBO, bool clearColor, bool clearDepth, bool clearStencil, const glm::vec4 & color, unsigned int stencil);
	void Draw (unsigned int FBO, unsigned int VAO, unsigned int shader, const DrawCommand & command, unsigned int elementCount);
	
	unsigned int CreateShader (const char * vertexCode, const char * fragmentCode);
};

}
