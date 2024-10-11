#include "GL/freeglut.h"
#include "glm/gtc/constants.hpp"
#include "glm/trigonometric.hpp"

#include "Torus.h"

Torus::Torus(const glm::vec3& position, float torusRadius, float circleRadius, int segments, int sides) :
	m_mesh(position)
{
	if (segments < 3 || sides < 3)
	{
		return;
	}

	//Pushing vertices
	for (int i = 0; i < segments; i++)
	{
		float sinXZ = glm::sin(i * glm::two_pi<float>() / (float)segments);
		float cosXZ = glm::cos(i * glm::two_pi<float>() / (float)segments);

		for (int j = 0; j < sides; j++)
		{
			float sinXY = glm::sin(j * glm::two_pi<float>() / (float)sides);
			float cosXY = glm::cos(j * glm::two_pi<float>() / (float)sides);

			m_mesh.m_v_vn.push_back(std::make_pair(position +
				glm::vec3(torusRadius * cosXZ + circleRadius * cosXZ * cosXY, circleRadius * sinXY, torusRadius * sinXZ + circleRadius * cosXY * sinXZ),
				glm::vec3()));
		}
	}

	//Pushing faces
	int vi1;
	int vi2;
	int vi3;
	int vi4;

	for (int i = 0; i < segments - 1; i++)
	{
		for (int j = 0; j < sides - 1; j++)
		{
			vi1 = sides * i + j;
			vi2 = vi1 + 1;
			vi3 = vi1 + sides;
			vi4 = vi3 + 1;
			m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(vi1, vi2, vi3), glm::vec3()));
			m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(vi2, vi4, vi3), glm::vec3()));
		}

		vi2 = sides * i;
		vi4 = vi2 + sides;
		vi1 = vi4 - 1;
		vi3 = vi1 + sides;
		m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(vi1, vi2, vi3), glm::vec3()));
		m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(vi2, vi4, vi3), glm::vec3()));
	}

	for (int i = 0; i < sides - 1; i++)
	{
		vi3 = i;
		vi4 = i + 1;
		vi1 = sides * (segments - 1) + vi3;
		vi2 = vi1 + 1;

		m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(vi1, vi2, vi3), glm::vec3()));
		m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(vi2, vi4, vi3), glm::vec3()));
	}

	vi4 = 0;
	vi3 = sides - 1;
	vi2 = sides * (segments - 1);
	vi1 = sides * (segments - 1) + vi3;
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(vi1, vi2, vi3), glm::vec3()));
	m_mesh.m_f_fn.push_back(std::make_pair(glm::ivec3(vi2, vi4, vi3), glm::vec3()));

	//Calculating normals
	m_mesh.calcNormals();
}

void Torus::render()
{
	m_mesh.render();
}
