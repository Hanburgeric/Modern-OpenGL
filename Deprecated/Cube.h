#ifndef CUBE_H
#define CUBE_H

#include "glm/vec3.hpp"

#include "Mesh.h"

class Cube
{
public:
	Cube(const glm::vec3& position, float length);

	void render();

	Mesh m_mesh;
};

#endif
