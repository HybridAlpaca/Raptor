#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera (glm::vec3 position, glm::vec3 up)
: front (glm::vec3(0.0f, 0.0f, -1.0f))
, position (position)
, up (up)
, worldUp (up)
{
	UpdateVectors();
}

Camera::~Camera ()
{}

glm::mat4 Camera::ViewMatrix ()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard (CameraControl direction, float delta)
{
	float velocity = MOVEMENT_SPEED * delta;
	
	switch (direction)
	{
		case CameraControl::FORWARD:
			position += front * velocity;
			break;
		case CameraControl::BACKWARD:
			position -= front * velocity;
			break;
		case CameraControl::LEFT:
			position -= right * velocity;
			break;
		case CameraControl::RIGHT:
			position += right * velocity;
			break;
	}
}

void Camera::UpdateVectors ()
{
	glm::vec3 nfront;
	nfront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	nfront.y = sin(glm::radians(pitch));
	nfront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(nfront);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up    = glm::normalize(glm::cross(right, front));
}
