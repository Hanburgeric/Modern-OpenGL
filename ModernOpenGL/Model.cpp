#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>
#include <iostream>
#include <stb/stb_image.h>

#include "Model.h"
#include "Shader.h"

Model::Model(const std::string& modelPath, bool flipTexCoord)
{
	m_directory = modelPath.substr(0, modelPath.find_last_of("/"));
	if (flipTexCoord)
	{
		m_flipTexCoordFlag = 0x800000;
	}
	else
	{
		m_flipTexCoordFlag = 0x0;
	}
	loadModel(modelPath);
}

Model::~Model()
{
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].destroyMesh();
	}
}

void Model::render(Shader& shader) const
{
	for (int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].render(shader);
	}
}

void Model::loadModel(const std::string& modelPath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelPath, aiProcessPreset_TargetRealtime_MaxQuality | m_flipTexCoordFlag);
	if (!scene)
	{
		std::cout << "Failed to load model" << std::endl;
		return;
	}
	loadNode(scene->mRootNode, scene);
}

void Model::loadNode(const aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		loadNode(node->mChildren[i], scene);
	}
}

void Model::loadMesh(const aiMesh* mesh, const aiScene* scene)
{
	Mesh newMesh;

	//Pushes vertices
	for (unsigned int vertexIndex = 0; vertexIndex < mesh->mNumVertices; vertexIndex++)
	{
		Vertex newVertex;

		//Positions
		if (mesh->HasPositions())
		{
			newVertex.m_position = glm::vec3(mesh->mVertices[vertexIndex].x, mesh->mVertices[vertexIndex].y, mesh->mVertices[vertexIndex].z);
		}

		//Texture coordinates
		for (int texCoordIndex = 0; texCoordIndex < AI_MAX_NUMBER_OF_TEXTURECOORDS; texCoordIndex++)
		{
			if (mesh->HasTextureCoords(texCoordIndex))
			{
				newVertex.m_texCoord[texCoordIndex] = glm::vec2(mesh->mTextureCoords[texCoordIndex][vertexIndex].x, mesh->mTextureCoords[texCoordIndex][vertexIndex].y);
			}
			else
			{
				newVertex.m_texCoord[texCoordIndex] = glm::vec2();
			}
		}

		//Normals
		if (mesh->HasNormals())
		{
			newVertex.m_normal = glm::vec3(mesh->mNormals[vertexIndex].x, mesh->mNormals[vertexIndex].y, mesh->mNormals[vertexIndex].z);
		}

		//Tangents and bitangents
		if (mesh->HasTangentsAndBitangents())
		{
			newVertex.m_tangent = glm::vec3(mesh->mTangents[vertexIndex].x, mesh->mTangents[vertexIndex].y, mesh->mTangents[vertexIndex].z);
			newVertex.m_bitangent = glm::vec3(mesh->mBitangents[vertexIndex].x, mesh->mBitangents[vertexIndex].y, mesh->mBitangents[vertexIndex].z);
		}

		newMesh.pushVertex(newVertex);
	}

	//Pushes indices
	for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; faceIndex++)
	{
		for (unsigned int index = 0; index < mesh->mFaces[faceIndex].mNumIndices; index++)
		{
			newMesh.pushIndex(mesh->mFaces[faceIndex].mIndices[index]);
		}
	}

	//Pushes textures
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	loadTextures(newMesh, material, aiTextureType_DIFFUSE, "uTexDiffuse");

	//Creates and pushes mesh
	newMesh.createMesh();
	m_meshes.push_back(newMesh);
}

void Model::loadTextures(Mesh& mesh, const aiMaterial* material, const aiTextureType& texType, const std::string& texTypeName)
{
	for (unsigned int texTypeCount = 0; texTypeCount < material->GetTextureCount(texType); texTypeCount++)
	{
		aiString texName;
		material->GetTexture(texType, texTypeCount, &texName);
		std::string texNameStr = std::string(texName.C_Str());

		bool isLoaded = false;
		for (unsigned int i = 0; i < m_loadedTextures.size(); i++)
		{
			if (m_loadedTextures[i].m_texName == texNameStr)
			{
				mesh.pushTexture(m_loadedTextures[i]);
				isLoaded = true;
				break;
			}
		}

		if (!isLoaded)
		{
			Texture texture;
			texture.m_texName = texNameStr;
			texture.m_texType = texTypeName;
			texture.m_texID = loadTexture(m_directory + "/" + texNameStr);
			mesh.pushTexture(texture);
			m_loadedTextures.push_back(texture);
		}
	}
}

unsigned int Model::loadTexture(const std::string& texPath)
{
	unsigned int texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	int width;
	int height;
	int numChannels;
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, format, GL_UNSIGNED_BYTE, pixelData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(pixelData);
	}
	else
	{
		std::cout << "Failed to load texture at " << texPath << std::endl;
	}

	return texID;
}
