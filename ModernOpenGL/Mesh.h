#ifndef MESH_H
#define MESH_H

#include <assimp/mesh.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

class Shader;

struct Vertex
{
	glm::vec3 m_position;
	glm::vec2 m_texCoord[AI_MAX_NUMBER_OF_TEXTURECOORDS];
	glm::vec3 m_normal;
	glm::vec3 m_tangent;
	glm::vec3 m_bitangent;
};

struct Texture
{
	std::string m_texName;
	std::string m_texType;
	unsigned int m_texID;
};

class Mesh
{
public:
	void createMesh();
	void destroyMesh();

	void pushVertex(const Vertex& vertex);
	void pushIndex(unsigned int index);
	void pushTexture(const Texture& texture);

	void render(Shader& shader) const;

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;

	unsigned int m_vaoID;
	unsigned int m_vboID;
	unsigned int m_iboID;
};

#endif
