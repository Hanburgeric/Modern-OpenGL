#include <glad/glad.h>
#include <iostream>

#include "Mesh.h"
#include "Shader.h"

void Mesh::createMesh()
{
	glGenVertexArrays(1, &m_vaoID);
	glBindVertexArray(m_vaoID);

	glGenBuffers(1, &m_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_texCoord));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_normal));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_tangent));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, m_bitangent));
}

void Mesh::destroyMesh()
{
	glDeleteBuffers(1, &m_iboID);
	glDeleteBuffers(1, &m_vboID);
	glDeleteVertexArrays(1, &m_vaoID);
}

void Mesh::pushVertex(const Vertex& vertex)
{
	m_vertices.push_back(vertex);
}

void Mesh::pushIndex(unsigned int index)
{
	m_indices.push_back(index);
}

void Mesh::pushTexture(const Texture& texture)
{
	m_textures.push_back(texture);
}

void Mesh::render(Shader& shader) const
{
	unsigned int diffuseIndex = 1;

	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string texTypeStr = m_textures[i].m_texType;
		std::string texTypeIndexStr;

		if (texTypeStr == "uTexDiffuse")
		{
			texTypeIndexStr = std::to_string(diffuseIndex);
			diffuseIndex++;
		}
		else
		{
			std::cout << "Failed to recognize " << texTypeStr << " as a valid texture type" << std::endl;
			continue;
		}

		shader.setUniform1ui(texTypeStr + texTypeIndexStr, i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i].m_texID);
	}

	glBindVertexArray(m_vaoID);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (const void*)0);
}
