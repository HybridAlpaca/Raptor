#include "Vector.h"

Vector::Vector () : x(0.0f), y(0.0f), z(0.0f), w(0.0f), type(VecType::VEC4) {}

Vector::Vector (const Vector & vec) {}

Vector::Vector (float x, float y) : x(x), y(y), type(VecType::VEC2) {}

Vector::Vector (float x, float y, float z) : x(x), y(y), z(z), type(VecType::VEC3) {}

Vector::Vector (float x, float y, float z, float w) : x(x), y(y), z(z), w(w), type(VecType::VEC4) {}

bool Vector::operator == (const Vector & rhs) const {

	return x == rhs.x
			&& y == rhs.y
			&& z == rhs.z
			&& w == rhs.w;

}

bool Vector::operator != (const Vector & rhs) const {

	return false; // TODO

}