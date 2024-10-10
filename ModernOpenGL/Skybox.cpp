#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>

#include "Skybox.h"
#include "Shader.h"

Skybox::Skybox(const std::string& skyboxPath, const std::string& imageFormat)
{
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), m_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices), m_indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);

	glGenTextures(1, &m_cubemapID);
	glBindTexture(GL_TEXTURE_2D, m_cubemapID);

	loadCubemap(skyboxPath, imageFormat);
}

void Skybox::render(Shader& shader)
{
	glActiveTexture(GL_TEXTURE0);
	shader.setUniform1ui("uSkybox", m_cubemapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubemapID);
	glBindVertexArray(m_vaoID);
	glDepthFunc(GL_LEQUAL);
	glDrawElements(GL_TRIANGLES, sizeof(m_indices) / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
	glDepthFunc(GL_LESS);
}

void Skybox::loadCubemap(const std::string& skyboxPath, const std::string& imageFormat)
{
	std::string faces[6] = { "right", "left", "top", "bottom", "front", "back" };
	int width;
	int height;
	int numChannels;
	for (int i = 0; i < sizeof(faces) / sizeof(std::string); i++)
	{
		std::string texPath = skyboxPath + faces[i] + imageFormat;
		unsigned char* pixelData = stbi_load(texPath.c_str(), &width, &height, &numChannels, 0);
		if (pixelData)
		{
			GLenum format;
			switch (numChannels)
			{
			case 3:
			{
				format = GL_RGB;
				break;
			}
			case 4:
			{
				format = GL_RGBA;
				break;
			}
			}

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, format, GL_UNSIGNED_BYTE, pixelData);
			stbi_image_free(pixelData);
		}
		else
		{
			std::cout << "Failed to load texture at " << texPath << std::endl;
		}
	}
}
