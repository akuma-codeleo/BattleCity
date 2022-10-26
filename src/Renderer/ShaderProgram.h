#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& ShaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& ShaderProgram) noexcept;

		bool isCompiled() const { return m_isCompiled; }
		void use() const;
		void setInt(const std::string& name, const GLint value);

	private:
		bool m_isCompiled = false;
		GLuint m_ID = 0;

		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
	};
}