#ifndef MESH_H
#define MESH_H

#include "glm/vec3.hpp"
#include <vector>
#include <utility>

class Mesh
{
public:
	Mesh(const glm::vec3& position);

	void calcNormals();

	void scale(const glm::vec3& scalingVector);
	void rotate(float angleDeg, const glm::vec3 origin, const glm::vec3& rotationVector);
	void translate(const glm::vec3& translationVector);

	void render();

	glm::vec3 m_position;
	std::vector<std::pair<glm::vec3, glm::vec3>> m_v_vn;
	std::vector<std::pair<glm::ivec3, glm::vec3>> m_f_fn;
	bool toggleDisplay[5];
};

#endif
