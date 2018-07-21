#pragma once

#include <glm/glm.hpp>

enum class CameraControl
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

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

	Camera (glm::vec3 position = glm::vec3(0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	Camera (const Camera & copy);
	~Camera ();
	
	Camera & operator= (const Camera & copy);
	
	void ProcessKeyboard (CameraControl direction, float delta);
	void ProcessMouse (float deltaX, float deltaY, bool constrainPitch = true);
	
	glm::mat4 ViewMatrix ();
};
