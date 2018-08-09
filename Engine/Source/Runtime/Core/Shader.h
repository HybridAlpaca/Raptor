#pragma once

#include <glm/glm.hpp>

/**
 *
 * @class Shader
 * @headerfile Shader.h <Core/Shader.h>
 * @author Seth Traman
 * @date August 2018
 *
 * @brief Partial-RAII wrapper class around an OpenGL shader program object.
 *
 * @deprecated Shader can be expected to be factored out in a near-future update.  This will be accompanied by several other rendering-related changes.
 *
 * @warning This class does not free allocated GL resources on destruction, so you may want to manually track shader ID's and free them yourself.  This is not expected to be implemented due to the class's limited lifespan.
 *
 **/

class Shader
{
	unsigned int ID; ///< OpenGL resource ID of shader program obect

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
