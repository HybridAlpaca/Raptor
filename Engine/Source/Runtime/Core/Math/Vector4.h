#pragma once

#include <Core/Common/Required.h>

namespace Core
{
namespace Math
{

class Vec4
{
	float x, y, z, w;
	
public:

	Vec4 ();
	Vec4 (float val);
	Vec4 (float x, float y, float z, float w);
	Vec4 (const Vec4 & copy);
	
	Vec4 & operator= (const Vec4 & rhs);
	Vec4 & operator= (float val);
	Vec4 & operator+ (const Vec4 & rhs);
	Vec4 & operator- (const Vec4 & rhs);
	Vec4 & operator+= (float val);
	Vec4 & operator-= (float val);
	
	const float x () const { return x; }
	const float y () const { return y; }
	const float z () const { return z; }
	const float w () const { return w; }
	// alternate
	const float r () const { return r; }
	const float g () const { return g; }
	const float b () const { return b; }
	const float a () const { return a; }
	
	void x (float val) { x = val; }
	void y (float val) { y = val; }
	void z (float val) { z = val; }
	void w (float val) { w = val; }
	// alternate
	void r (float val) { r = val; }
	void g (float val) { g = val; }
	void b (float val) { b = val; }
	void a (float val) { a = val; }
};

}
}