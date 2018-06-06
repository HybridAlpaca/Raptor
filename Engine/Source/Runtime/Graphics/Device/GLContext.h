#pragma once

namespace Graphics::Device
{

class OpenGLContext
{
	uint32 boundVAO	= 0;
	uint32 boundShader = 0;
	uint32 boundFBO	= 0;
	uint32 viewportFBO = 0;

public:

	enum class BufferUsage
	{
		STATIC_DRAW = GL_STATIC_DRAW,
		STREAM_DRAW = GL_STREAM_DRAW,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		
		STATIC_COPY = GL_STATIC_COPY,
		STREAM_COPY = GL_STREAM_COPY,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		
		STATIC_READ = GL_STATIC_READ,
		STREAM_READ = GL_STREAM_READ,
		DYNAMIC_READ = GL_DYNAMIC_READ
	};
	enum class SamplerFilter
	{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
	};
	enum class SamplerWrapMode
	{
		CLAMP = GL_CLAMP_TO_EDGE,
		REPEAT = GL_REPEAT,
		CLAMP_MIRROR = GL_MIRROR_CLAMP_TO_EDGE,
		REPEAT_MIRROR = GL_MIRRORED_REPEAT,
	};
	enum class PrimitiveType
	{
		TRIANGLES = GL_TRIANGLES,
		POINTS = GL_POINTS,
		LINE_STRIP = GL_LINE_STRIP,
		LINE_LOOP = GL_LINE_LOOP,
		LINES = GL_LINES,
		LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
		LINES_ADJACENCY = GL_LINES_ADJACENCY,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		TRAINGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
		PATCHES = GL_PATCHES,
	};
	enum class DrawFunc
	{
		NEVER = GL_NEVER,
		ALWAYS = GL_ALWAYS,
		LESS = GL_LESS,
		GREATER = GL_GREATER,
		LEQUAL = GL_LEQUAL,
		GEQUAL = GL_GEQUAL,
		EQUAL = GL_EQUAL,
		NOTEQUAL = GL_NOTEQUAL,
	};
	enum class FBAttachment
	{
		COLOR = GL_COLOR_ATTACHMENT0,
		DEPTH = GL_DEPTH_ATTACHMENT,
		STENCIL = GL_STENCIL_ATTACHMENT,
	};
	enum class StencilOp
	{
		KEEP = GL_KEEP,
		ZERO = GL_ZERO,
		REPLACE = GL_REPLACE,
		INCR = GL_INCR,
		INCR_WRAP = GL_INCR_WRAP,
		DECR_WRAP = GL_DECR_WRAP,
		DECR = GL_DECR,
		INVERT = GL_INVERT,
	};
	enum class CullState
	{
		NONE,
		BACK = GL_BACK,
		FRONT = GL_FRONT,
		FRONT_AND_BACK = GL_FRONT_AND_BACK,
	};
	enum class BlendFunc
	{
		NONE,
		ONE = GL_ONE,
		SRC_ALPHA = GL_SRC_ALPHA,
		ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
		ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
		DST_ALPHA = GL_DST_ALPHA,
	};
	enum class PixelFormat
	{
		R,
		RG,
		RGB,
		RGBA,
		DEPTH,
		DEPTH_AND_STENCIL,
	};
	
	struct RenderParams
	{
		int32 stencilComparisonVal = 0;
		uint32 stencilTestMask = 0;
		uint32 stencilWriteMask = 0;
		
		BlendFunc sourceBlend = BlendFunc::NONE;
		BlendFunc destBlend = BlendFunc::NONE;
		CullState cullState = CullState::None;
		DrawFunc depthFunc = DrawFunc::Always;
		DrawFunc stencilFunc = DrawFunc::Always;
		PrimitiveType primitiveType = PrimitiveType::Triangles;
		StencilOp stencilFail = StencilOp::KEEP;
		StencilOp stencilPassDepthFail = StencilOp::KEEP;
		StencilOp stencilPass = StencilOp::KEEP;
		
		bool writeDepth = true;
		bool stencilTest = false;
	};
};

}