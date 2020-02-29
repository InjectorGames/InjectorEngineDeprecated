#include <injector_engine.h>

namespace Injector
{
	GLuint Material::CreateProgram()
	{
		return glCreateProgram();
	}
	void Material::DeleteProgram(GLuint program)
	{
		glDeleteProgram(program);
	}

	void Material::AttachShader(GLuint program, GLuint shader)
	{
		glAttachShader(program, shader);
	}
	void Material::DetachShader(GLuint program, GLuint shader)
	{
		glDetachShader(program, shader);
	}

	void Material::LinkProgram(GLuint program)
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

	GLuint Material::GetUniformLocation(GLuint program, const std::string& name)
	{
		auto location = glGetUniformLocation(program, name.c_str());

		if (location == -1)
			throw std::runtime_error("Failed to get material uniform location");

		return location;
	}
	GLuint Material::GetUniform(const std::string& name) const
	{
		return GetUniformLocation(program, name);
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

	Material::Material(std::shared_ptr<Shader> shader) : program(CreateProgram())
	{
		auto shaderName = shader->shader;
		AttachShader(program, shaderName);
		LinkProgram(program);
		DetachShader(program, shaderName);
		UseProgram();
	}
	Material::Material(std::shared_ptr<Shader> shader1, std::shared_ptr<Shader> shader2) : program(CreateProgram())
	{
		auto shaderName1 = shader1->shader;
		auto shaderName2 = shader2->shader;

		AttachShader(program, shaderName1);
		AttachShader(program, shaderName2);

		LinkProgram(program);

		DetachShader(program, shaderName1);
		DetachShader(program, shaderName2);

		UseProgram();
	}
	Material::Material(std::shared_ptr<Shader> shader1, std::shared_ptr<Shader> shader2, std::shared_ptr<Shader> shader3) : program(CreateProgram())
	{
		auto shaderName1 = shader1->shader;
		auto shaderName2 = shader2->shader;
		auto shaderName3 = shader3->shader;

		AttachShader(program, shaderName1);
		AttachShader(program, shaderName2);
		AttachShader(program, shaderName3);

		LinkProgram(program);

		DetachShader(program, shaderName1);
		DetachShader(program, shaderName2);
		DetachShader(program, shaderName3);

		UseProgram();
	}

	Material::~Material()
	{
		DeleteProgram(program);
	}

	void Material::UseProgram() const
	{
		glUseProgram(program);
	}
	void Material::UnuseProgram()
	{
		glUseProgram(GL_ZERO);
	}

	// TODO: add program pipeline support
}
