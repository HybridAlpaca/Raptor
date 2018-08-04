#pragma once

#include <glm/glm.hpp>

class Shader
{
	unsigned int ID;

public:

	Shader (const char * vertPath, const char * fragPath);
	Shader (const Shader & copy) = delete;
	~Shader ();
	
	Shader & operator= (const Shader & rhs) = delete;
	
	void Bind ();
	
	void Bool (const char * name, bool val) const;
	void Float (const char * name, float val) const;
	void Int (const char * name, int val) const;
	
	void Vec2 (const char * name) const;
	void Vec3 (const char * name, const glm::vec3 & val) const;
	void Vec4 (const char * name) const;
	
	void Mat3 (const char * name, const glm::mat3 & val) const;
	void Mat4 (const char * name, const glm::mat4 & val) const;
	
	constexpr unsigned int id () const { return ID; }

};
