#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <vector>

#include "Camera.h"
#include "InputManager.h"

Camera::Camera(const glm::vec3& position, const glm::vec3& worldUp, float yaw, float pitch, float fov, float near, float far)
{
	m_position = position;
	m_worldUp = worldUp;
	m_yaw = yaw;
	m_pitch = pitch;
	m_fov = fov;
	m_near = near;
	m_far = far;

	update();
}

void Camera::handleInput(const InputManager& inputManager)
{
	if (inputManager.isMouseHeld(GLFW_MOUSE_BUTTON_MIDDLE))
	{
		if (inputManager.isKeyHeld(GLFW_KEY_LEFT_ALT))
		{
			m_yaw = glm::mod(m_yaw + 0.15f * inputManager.getCursorX().m_deltaPos, 360.0f);
			m_pitch = glm::mod(m_pitch - 0.15f * inputManager.getCursorY().m_deltaPos, 360.0f);
		}

		else
		{
			m_position -= 0.05f * inputManager.getCursorX().m_deltaPos * m_right;
			m_position += 0.05f * inputManager.getCursorY().m_deltaPos * m_up;
		}
	}

	m_position += 2.5f * inputManager.getScrollOffsetY() * m_front;
}

void Camera::update()
{
	float sinYaw = glm::sin(glm::radians(m_yaw));
	float cosYaw = glm::cos(glm::radians(m_yaw));
	float sinPitch = glm::sin(glm::radians(m_pitch));
	float cosPitch = glm::cos(glm::radians(m_pitch));

	m_front = glm::normalize(glm::vec3(cosYaw * cosPitch, sinPitch, sinYaw * cosPitch));
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const
{
	return glm::perspective(glm::radians(m_fov), aspectRatio, m_near, m_far);
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}
