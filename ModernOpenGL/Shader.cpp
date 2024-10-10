#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

#include "Shader.h"

Shader::Shader()
{
	m_programID = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(m_programID);
}

void Shader::bind() const
{
	glUseProgram(m_programID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::pushShader(unsigned int shaderType, const std::string& shaderPath)
{
	std::string shaderStr = parseShader(shaderPath);
	const char* shaderCStr = shaderStr.c_str();

	unsigned int shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCStr, nullptr);
	glCompileShader(shaderID);
	if (!isShaderCompiled(shaderID))
	{
		std::cout << "Failed to compile shader" << std::endl;
	}
	else
	{
		m_shaderIDs.push_back(shaderID);
	}
}

void Shader::createProgram()
{
	for (int i = 0; i < m_shaderIDs.size(); i++)
	{
		glAttachShader(m_programID, m_shaderIDs[i]);
	}

	glLinkProgram(m_programID);
	if (!isProgramLinked())
	{
		std::cout << "Failed to link program" << std::endl;
	}

	glValidateProgram(m_programID);
	if (!isProgramValidated())
	{
		std::cout << "Failed to validate program" << std::endl;
	}

	for (int i = 0; i < m_shaderIDs.size(); i++)
	{
		glDetachShader(m_programID, m_shaderIDs[i]);
		glDeleteShader(m_shaderIDs[i]);
	}

	m_shaderIDs.clear();
}

int Shader::getUniformLocation(const std::string& name)
{
	if (m_uniformLocations.find(name) == m_uniformLocations.end())
	{
		m_uniformLocations[name] = glGetUniformLocation(m_programID, name.c_str());
	}
	return m_uniformLocations[name];
}

void Shader::setUniform1f(const std::string& name, float v0)
{
	glUniform1f(getUniformLocation(name), v0);
}

void Shader::setUniform1i(const std::string& name, int v0)
{
	glUniform1i(getUniformLocation(name), v0);
}

void Shader::setUniform1ui(const std::string& name, unsigned int v0)
{
	glUniform1ui(getUniformLocation(name), v0);
}

void Shader::setUniform3fv(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setUniform4fv(const std::string& name, const glm::vec4& value)
{
	glUniform4fv(getUniformLocation(name), 1, &value[0]);
}

void Shader::setUniformMatrix4fv(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

std::string Shader::parseShader(const std::string& shaderPath) const
{
	std::stringstream shaderStream;

	std::ifstream shaderFile(shaderPath);
	if (!shaderFile)
	{
		std::cout << "Failed to read file: " << shaderPath << std::endl;
	}
	else
	{
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
	}

	return shaderStream.str();
}

bool Shader::isShaderCompiled(unsigned int shaderID) const
{
	int isCompiled;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isCompiled);
	return isCompiled;
}

bool Shader::isProgramLinked() const
{
	int isLinked;
	glGetProgramiv(m_programID, GL_LINK_STATUS, &isLinked);
	return isLinked;
}

bool Shader::isProgramValidated() const
{
	int isValidated;
	glGetProgramiv(m_programID, GL_VALIDATE_STATUS, &isValidated);
	return isValidated;
}
