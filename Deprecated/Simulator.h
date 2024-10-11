#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include <vector>

#include "Cube.h"
#include "Torus.h"

class Simulator
{
public:
	Simulator();
	~Simulator();

	void init();
	void cleanup();

	void motion(int x, int y);
	void mouse(int mouseEvent, int mouseState, int x, int y);
	void keyboard(unsigned char key, int x, int y);
	void specialFunc(int key, int x, int y);
	void update(int value);
	void render();
	void reshape(int width, int height);

	bool m_start[2];
	glm::ivec2 m_mousePos;
	bool m_mouseEvent[2];
	glm::vec3 m_translate;
	glm::vec2 m_rotate;

	std::vector<Cube> m_cubes;
	std::vector<Torus> m_toruses;
};

#endif
