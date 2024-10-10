#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

class InputManager;

class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& worldUp, float yaw, float pitch, float fov, float near, float far);

	void handleInput(const InputManager& inputManager);
	void update();

	glm::mat4 getProjectionMatrix(float aspectRatio) const;
	glm::mat4 getViewMatrix() const;

private:
	glm::vec3 m_position;
	glm::vec3 m_front;
	glm::vec3 m_up;
	glm::vec3 m_right;
	glm::vec3 m_worldUp;

	float m_yaw;
	float m_pitch;

	float m_fov;
	float m_near;
	float m_far;
};

#endif
