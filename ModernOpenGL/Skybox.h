#ifndef SKYBOX_H
#define SKYBOX_H

#include <string>

class Shader;

class Skybox
{
public:
	Skybox(const std::string& skyboxPath, const std::string& imageFormat);

	void render(Shader& shader);

private:
	void loadCubemap(const std::string& skyboxPath, const std::string& imageFormat);

private:
	float m_vertices[24] = {
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f
	};

	unsigned int m_indices[36] = {
		5, 7, 6,	//Positive X
		4, 5, 6,
		0, 3, 1,	//Negative X
		0, 2, 3,
		2, 6, 7,	//Positive Y
		2, 7, 3,
		1, 5, 4,	//Negative Y
		0, 1, 4,
		1, 3, 7,	//Positive Z
		1, 7, 5,
		0, 4, 2,	//Negative Z
		2, 4, 6,
	};

	unsigned int m_vaoID;
	unsigned int m_vboID;
	unsigned int m_iboID;
	unsigned int m_cubemapID;
};

#endif
