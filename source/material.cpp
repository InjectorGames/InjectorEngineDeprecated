#include <injector_engine.h>

namespace Injector
{
	void Material::AttachShader(GLuint shader)
	{
		glAttachShader(program, shader);
	}
	void Material::DetachShader(GLuint shader)
	{
		glDetachShader(program, shader);
	}

	void Material::LinkProgram()
	{
		glLinkProgram(program);

		GLint success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::string buffer(maxLength, ' ');
			glGetProgramInfoLog(program, maxLength, &maxLength, &buffer[0]);

			throw std::runtime_error("Failed to link program. " + buffer);
		}
	}

	GLuint Material::GetUniformLocation(const std::string& name)
	{
		auto location = glGetUniformLocation(program, name.c_str());

		if (location == -1)
			throw std::runtime_error("Failed to get material uniform location");

		return location;
	}

	void Material::SetUniform(GLint index, GLfloat value)
	{
		glUniform1f(index, value);
	}
	void  Material::SetUniform(GLint index, const glm::vec2& value)
	{
		glUniform2fv(index, GL_ONE, value_ptr(value));
	}
	void Material::SetUniform(GLint index, const glm::vec3& value)
	{
		glUniform3fv(index, GL_ONE, value_ptr(value));
	}
	void Material::SetUniform(GLint index, const glm::vec4& value)
	{
		glUniform4fv(index, GL_ONE, value_ptr(value));
	}
	void Material::SetUniform(GLint index, const glm::mat2& value)
	{
		glUniformMatrix2fv(index, GL_ONE, GL_FALSE, value_ptr(value));
	}
	void Material::SetUniform(GLint index, const glm::mat3& value)
	{
		glUniformMatrix3fv(index, GL_ONE, GL_FALSE, value_ptr(value));
	}
	void Material::SetUniform(GLint index, const glm::mat4& value)
	{
		glUniformMatrix4fv(index, GL_ONE, GL_FALSE, value_ptr(value));
	}

	Material::Material()
	{
		program = glCreateProgram();
	}
	Material::~Material()
	{
		glDeleteProgram(program);
	}

	GLuint Material::GetProgram()
	{
		return program;
	}
	void Material::UseProgram()
	{
		glUseProgram(program);
	}

	// TODO: add program pipeline support
}
