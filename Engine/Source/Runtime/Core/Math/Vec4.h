#pragma once

#include <Core/Common/Required.h>

namespace Core
{
namespace Math
{

struct Vec4
{
	float values[4];

	Vec4 ();
	Vec4 (float val[4]);
	Vec4 (float x, float y, float z, float w);
	Vec4 (const Vec4 & copy);
	
	Vec4 & operator= (const Vec4 & rhs);
	Vec4 & operator= (float val);
	Vec4 & operator+ (const Vec4 & rhs);
	Vec4 & operator- (const Vec4 & rhs);
	Vec4 & operator+= (float val);
	Vec4 & operator-= (float val);
	
	const float x () const { return values[0]; }
	const float y () const { return values[1]; }
	const float z () const { return values[2]; }
	const float w () const { return values[3]; }
	// alternate
	const float r () const { return values[0]; }
	const float g () const { return values[1]; }
	const float b () const { return values[2]; }
	const float a () const { return values[3]; }
	
	void x (float val) { values[0] = val; }
	void y (float val) { values[1] = val; }
	void z (float val) { values[2] = val; }
	void w (float val) { values[3] = val; }
	// alternate
	void r (float val) { values[0] = val; }
	void g (float val) { values[1] = val; }
	void b (float val) { values[2] = val; }
	void a (float val) { values[3] = val; }
};

}
}