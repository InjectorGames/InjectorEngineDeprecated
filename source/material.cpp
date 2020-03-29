#include <injector_engine.h>

namespace Injector
{
	void Material::Attach(GLuint shader) const
	{
		glAttachShader(program, shader);
	}
	void Material::Detach(GLuint shader) const
	{
		glDetachShader(program, shader);
	}

	void Material::Link() const
	{
		glLinkProgram(program);

		auto success = (GLint)0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success == GL_FALSE)
		{
			auto maxLength = (GLint)0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::string buffer(maxLength, ' ');
			glGetProgramInfoLog(program, maxLength, &maxLength, &buffer[0]);

			throw std::runtime_error("Failed to link program. " + buffer);
		}
	}

	GLuint Material::GetUniformLocation(const std::string& name) const
	{
		auto location = glGetUniformLocation(program, name.c_str());

		if (location == -1)
			throw std::runtime_error("Failed to get uniform location");

		return location;
	}

	void Material::SetUniform(GLint index, GLint value)
	{
		glUniform1i(index, value);
	}
	void Material::SetUniform(GLint index, GLfloat value)
	{
		glUniform1f(index, value);
	}
	void Material::SetUniform(GLint index, const glm::vec2& value)
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

	Material::Material(std::shared_ptr<Shader> shader, uint16_t _renderQueue) :
		program(glCreateProgram()),
		renderQueue(_renderQueue)
	{
		auto shaderName = shader->shader;
		Attach(shaderName);
		Link();
		Detach(shaderName);
		Use();
	}
	Material::Material(std::shared_ptr<Shader> shader1, std::shared_ptr<Shader> shader2, uint16_t _renderQueue) :
		program(glCreateProgram()),
		renderQueue(_renderQueue)
	{
		auto shaderName1 = shader1->shader;
		auto shaderName2 = shader2->shader;

		Attach(shaderName1);
		Attach(shaderName2);

		Link();

		Detach(shaderName1);
		Detach(shaderName2);

		Use();
	}
	Material::Material(std::shared_ptr<Shader> shader1, std::shared_ptr<Shader> shader2, std::shared_ptr<Shader> shader3, uint16_t _renderQueue) :
		program(glCreateProgram()),
		renderQueue(_renderQueue)
	{
		auto shaderName1 = shader1->shader;
		auto shaderName2 = shader2->shader;
		auto shaderName3 = shader3->shader;

		Attach(shaderName1);
		Attach(shaderName2);
		Attach(shaderName3);

		Link();

		Detach(shaderName1);
		Detach(shaderName2);
		Detach(shaderName3);

		Use();
	}

	Material::~Material()
	{
		glDeleteProgram(program);
	}

	void Material::Use() const
	{
		glUseProgram(program);
	}
	void Material::Release()
	{
		glUseProgram(GL_ZERO);
	}

	void Material::AddDrawer(std::shared_ptr<Drawer> drawer)
	{
		if (!drawers.emplace(drawer).second)
			throw std::runtime_error("Failed to add material drawer");
	}
	void Material::RemoveDrawer(std::shared_ptr<Drawer> drawer)
	{
		if (!drawers.erase(drawer))
			throw std::runtime_error("Failed to remove material drawer");
	}

	void Material::OnRender(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		Use();

		for (auto const& drawer : drawers)
			drawer->OnDraw();
	}

	// TODO: add program pipeline support
}
