#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include "Mesh.h"

struct aiMaterial;
struct aiMesh;
struct aiNode;
struct aiScene;
enum aiTextureType;
class Shader;

class Model
{
public:
	Model(const std::string& modelPath, bool flipTexCoord);
	~Model();

	void render(Shader& shader) const;

private:
	void loadModel(const std::string& modelPath);
	void loadNode(const aiNode* node, const aiScene* scene);
	void loadMesh(const aiMesh* mesh, const aiScene* scene);
	void loadTextures(Mesh& mesh, const aiMaterial* material, const aiTextureType& texType, const std::string& texTypeName);
	unsigned int loadTexture(const std::string& texPath);

private:
	std::string m_directory;
	std::vector<Mesh> m_meshes;
	std::vector<Texture> m_loadedTextures;
	int m_flipTexCoordFlag;
};

#endif
