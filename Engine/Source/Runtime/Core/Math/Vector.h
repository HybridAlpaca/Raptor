#pragma once

class Vector {

	enum class VecType { VEC2, VEC3, VEC4 };
	
	VecType type;

public:

	// properties

	float x, y, z, w;
	
	// constructors

	Vector ();
	
	Vector (const Vector & vec);

	Vector (float x, float y);
	
	Vector (float x, float y, float z);
	
	Vector (float x, float y, float z, float w);
	
	// operators
	
	bool		operator == (const Vector & rhs) const;
	
	bool		operator != (const Vector & rhs) const;
	
	Vector	operator + (const Vector & rhs) const;
	
	Vector	operator + (const float & rhs) const;
	
	Vector	operator - (const Vector & rhs) const;
	
	Vector	operator - (const float & rhs) const;
	
	Vector	operator * (const float & rhs) const;

	Vector	operator / (const float & rhs) const;
	
	// methods
	
	bool		IsZero ();
	
	void		MakeZero ();
	
	float		LengthSquared ();
	
	float 	Length ();
	
	void		Normalize ();
	
	bool		IsNormalized ();
	
	float 	Dot (const Vector & rhs) const;
	
	Vector 	Cross (const Vector & rhs) const;
	
	Vector	Lerp (const Vector & rhs, float t) const;
	
	void		Clamp (float min, float max);
	
	// getters
	
	VecType	Type () const;

};