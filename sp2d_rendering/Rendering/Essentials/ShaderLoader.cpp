#include "ShaderLoader.h"
#include <iostream>
#include <fstream>

GLuint SP2D::Rendering::ShaderLoader::CreateProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	const GLuint program = glCreateProgram();

	const GLuint vertex = CompileShader(GL_VERTEX_SHADER, vertexShader);
	const GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	if (vertex == 0 || fragment == 0)
		return 0;

	if (!LinkShaders(program, vertex, fragment))
	{
		std::cout << "Failed to Link Shaders!" << std::endl;
		return 0;
	}

	return program;
}

GLuint SP2D::Rendering::ShaderLoader::CompileShader(GLuint shaderType, const std::string& filePath)
{
	const GLuint shaderID = glCreateShader(shaderType);

	std::ifstream ifs(filePath);

	if (ifs.fail())
	{
		std::cout << "Shader Failed to open [" << filePath << "]" << std::endl;
		return 0;
	}

	std::string contents{ "" };
	std::string line;

	while (std::getline(ifs, line))
	{
		contents += line + "\n";
	}

	ifs.close();

	const char* contentsPtr = contents.c_str();
	glShaderSource(shaderID, 1, &contentsPtr, nullptr);

	glCompileShader(shaderID);

	if (!CompileSuccess(shaderID))
	{
		std::cout << "Failed to compile shader [" << filePath << "]" << std::endl;
		return 0;
	}

	return shaderID;

}

bool SP2D::Rendering::ShaderLoader::CompileSuccess(GLuint shader)
{
	GLint status;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		GLint maxLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		std::string errorLog(maxLength, ' ');

		glGetShaderInfoLog(shader, maxLength, &maxLength, errorLog.data());
		std::cout << "Shader Compilation Failed : " << std::string{ errorLog } << std::endl;

		glDeleteShader(shader);
		return false;
	}

	return true;
}

bool SP2D::Rendering::ShaderLoader::IsProgramValid(GLuint program)
{
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		GLint maxLength;
		glGetProgramiv(program, GL_LINK_STATUS, &status);

		std::string errorLog(maxLength, ' ');

		glGetProgramInfoLog(program, maxLength, &maxLength, errorLog.data());
		std::cout << "Program is not Valid: " << std::string{ errorLog } << std::endl;

		//glDeleteProgram(program);
		return false;
	}

	return true;
}

bool SP2D::Rendering::ShaderLoader::LinkShaders(GLuint program, GLuint vertexShader, GLuint fragmentShader)
{
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	if (!IsProgramValid(program))
	{
		glDeleteProgram(program);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return false;
	}

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	return true;

}

std::shared_ptr<SP2D::Rendering::Shader> SP2D::Rendering::ShaderLoader::Create(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	GLuint program = CreateProgram(vertexShaderPath, fragmentShaderPath);

	if (program)
		return std::make_shared<Shader>(program, vertexShaderPath, fragmentShaderPath);

	return nullptr;
}
