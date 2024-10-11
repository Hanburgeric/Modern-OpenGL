#include "GL/freeglut.h"

#include "Cube.h"

Cube::Cube(const glm::vec3& position, float length) :
	m_mesh(position)
{
	float halfLength = length * 0.5f;
	m_mesh.m_v_vn.push_back(std::make_pair(position + glm::vec3(-halfLength, -halfLength, -halfLength), glm::vec3()));
	m_mesh.m_v_vn.push_back(std::make_pair(position + glm::vec3(-halfLength, -halfLength, halfLength), glm::vec3()));
	m_mesh.m_v_vn.push_back(std::make_pair(position + glm::vec3(-halfLength, halfLength, -halfLength), glm::vec3()));
	m_mesh.m_v_vn.push_back(std::make_pair(position + glm::vec3(-halfLength, halfLength, halfLength), glm::vec3()));
	m_mesh.m_v_vn.push_back(std::make_pair(position + glm::vec3(halfLength, -halfLength, -halfLength), glm::vec3()));
	m_mesh.m_v_vn.push_back(std::make_pair(position + glm::vec3(halfLength, -halfLength, halfLength), glm::vec3()));
	m_mesh.m_v_vn.push_back(std::make_pair(position + glm::vec3(halfLength, halfLength, -halfLength), glm::vec3()));
	m_mesh.m_v_vn.push_back(std::make_pair(position + glm::vec3(halfLength, halfLength, halfLength), glm::vec3()));

	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(0, 1, 3), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(0, 3, 2), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(0, 2, 4), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(2, 6, 4), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(2, 7, 6), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(2, 3, 7), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(1, 7, 3), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(1, 5, 7), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(5, 6, 7), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(4, 6, 5), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(1, 4, 5), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(0, 4, 1), glm::vec3()));

	m_mesh.calcNormals();
}

void Cube::render()
{
	m_mesh.render();
}

