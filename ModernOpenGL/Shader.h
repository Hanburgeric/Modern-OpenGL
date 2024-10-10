#ifndef SHADER_H
#define SHADER_H

#include <glm/mat4x4.hpp>
#include <string>
#include <unordered_map>
#include <vector>

class Shader
{
public:
	Shader();
	~Shader();

	void bind() const;
	void unbind() const;

	void pushShader(unsigned int shaderType, const std::string& shaderPath);
	void createProgram();

	void setUniform1f(const std::string& name, float v0);
	void setUniform1i(const std::string& name, int v0);
	void setUniform1ui(const std::string& name, unsigned int v0);
	void setUniform3fv(const std::string& name, const glm::vec3& value);
	void setUniform4fv(const std::string& name, const glm::vec4& value);
	void setUniformMatrix4fv(const std::string& name, const glm::mat4& value);

private:
	std::string parseShader(const std::string& shaderPath) const;

	bool isShaderCompiled(unsigned int shaderID) const;
	bool isProgramLinked() const;
	bool isProgramValidated() const;

	int getUniformLocation(const std::string& name);

private:
	unsigned int m_programID;
	std::vector<unsigned int> m_shaderIDs;
	std::unordered_map<std::string, int> m_uniformLocations;
};

#endif
