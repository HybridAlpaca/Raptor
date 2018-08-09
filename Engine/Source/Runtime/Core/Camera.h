#pragma once

#include <glm/glm.hpp>

/**
 *
 * @class CameraControl
 * @headerfile Camera.h <Core/Camera.h>
 * @author Seth Traman
 * @date August 2018
 * 
 * @brief Contains integer control operations for meneuvering camera through 3D world space 
 * @relates Camera
 * 
 **/

enum class CameraControl
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

/**
 *
 * @class Camera
 * @headerfile Camera.h <Core/Camera.h>
 * @author Seth Traman
 * @date August 2018
 * 
 * @brief Describes a mathematical camera with a world position for use in rendering 
 * 
 **/

class Camera
{
	constexpr const static float MOVEMENT_SPEED = 2.5f;
	constexpr const static float SENSITIVITY = 0.1f;
	
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	
	float yaw = -90.0f;
	float pitch = 0.0f;
	
	void UpdateVectors ();

public:

	/// @brief Create camera in 3D space
	/// @param position : World space coordinates for camera. Defaults to origin
	/// @param up : Local space up vector for orienting camera.  Defaults to world up
	Camera (glm::vec3 position = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	
	/// Noncopyable
	Camera (const Camera & copy);
	
	/// Does nothing
	~Camera ();
	
	/// Noncopyable
	Camera & operator= (const Camera & copy);
	
	/// @brief Moves camera around world based on CameraControl operatives and engine delta time
	/// @param direction : Which way camera must move in world space
	/// @param delta : Engine delta time used to regulate movement speed across devices and framerates
	void ProcessKeyboard (CameraControl direction, float delta);
	
	/// @todo Implement this
	/// @warning This feature is not yet implemented.  Feel free to do so
	void ProcessMouse (float deltaX, float deltaY, bool constrainPitch = true);
	
	/// @brief Calculates Camera instance's view matrix
	/// @return 4x4 view matrix for calculating final rendered object positions
	glm::mat4 ViewMatrix ();
	
	/// @brief Getter method
	/// @return Read-only world space position of Camera instance
	inline const glm::vec3 & Position () const { return position; }
};
