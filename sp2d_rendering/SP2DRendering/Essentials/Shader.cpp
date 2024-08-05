#include "Shader.h"
#include <iostream>
#include <SP2DLogging/Log.h>

GLuint SP2D::Rendering::Shader::GetUniformLocation(const std::string& uniformName)
{
	auto uniformItr = m_UniformLocationMap.find(uniformName);
	if (uniformItr != m_UniformLocationMap.end())
		return uniformItr->second;

	GLuint location = glGetUniformLocation(m_ShaderProgramID, uniformName.c_str());

	if (location == GL_INVALID_INDEX)
	{
		SP2D_CORE_ERROR("Uniform [{0}] not found in Shader!", uniformName);
		return -1;
	}

	m_UniformLocationMap.emplace(uniformName, location);

	return location;
}

SP2D::Rendering::Shader::Shader(GLuint program, const std::string& vertexPath, const std::string& fragmentPath)
	: m_ShaderProgramID{ program }, m_sVertexPath{ vertexPath }, m_sFragmentPath{ fragmentPath }
{

}

SP2D::Rendering::Shader::~Shader()
{
	if (m_ShaderProgramID > 0)
		glDeleteProgram(m_ShaderProgramID);
}

void SP2D::Rendering::Shader::SetUniformInt(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void SP2D::Rendering::Shader::SetUniformMat4(const std::string& name, glm::mat4& mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

void SP2D::Rendering::Shader::Enable()
{
	glUseProgram(m_ShaderProgramID);
}

void SP2D::Rendering::Shader::Disable()
{
	glUseProgram(0);
}
