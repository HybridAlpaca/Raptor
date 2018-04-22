#include "Vector.h"

Vector::Vector () : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vector::Vector (const Vector & vec) {}

Vector::Vector (float x, float y) : x(x), y(y){}

Vector::Vector (float x, float y, float z) : x(x), y(y), z(z) {}

Vector::Vector (float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

bool Vector::operator == (const Vector & rhs) const {

	return x == rhs.x
			&& y == rhs.y
			&& z == rhs.z
			&& w == rhs.w;

}

bool Vector::operator != (const Vector & rhs) const {

	return !((* this).operator==(rhs));

}

Vector Vector::operator + (const Vector & rhs) const {

	return Vector(x + rhs.x, y + rhs.y, z + rhs.z, w);

}

Vector Vector::operator + (const float & rhs) const {

	return Vector(x + rhs, y + rhs, z + rhs, w);

}

Vector Vector::operator - (const Vector & rhs) const {

	return Vector(x - rhs.x, y - rhs.y, z - rhs.z, w);

}

Vector Vector::operator - (const float & rhs) const {

	return Vector(x - rhs, y - rhs, z - rhs, w);

}