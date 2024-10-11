#ifndef TORUS_H
#define TORUS_H

#include "glm/vec3.hpp"

#include "Mesh.h"

class Torus
{
public:
	Torus(const glm::vec3& position, float torusRadius, float circleRadius, int segments, int sides);

	void render();

	Mesh m_mesh;
};

#endif
