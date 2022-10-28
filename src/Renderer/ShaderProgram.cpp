#include "ShaderProgram.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER: Compile-time error" << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER: Compile-time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link-time error: ""\n" << infoLog << std::endl;
		}
		else
		{
			m_isCompiled = true;
		}
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& ShaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = ShaderProgram.m_ID;
		m_isCompiled = ShaderProgram.m_isCompiled;

		ShaderProgram.m_ID = 0;
		ShaderProgram.m_isCompiled = false;

		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& ShaderProgram) noexcept
	{
		m_ID = ShaderProgram.m_ID;
		m_isCompiled = ShaderProgram.m_isCompiled;

		ShaderProgram.m_ID = 0;
		ShaderProgram.m_isCompiled = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_ID);
	}


	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile-time error: ""\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}


	void ShaderProgram::use() const
	{
		glUseProgram(m_ID);
	}

	void ShaderProgram::setInt(const std::string& name, const GLint value)
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}