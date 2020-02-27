#include <injector_engine.h>

namespace Injector
{
	Shader::Shader(Type _type, const std::string& source)
	{
		type = _type;
		shader = glCreateShader((GLenum)_type);
		
		auto chars = (const GLchar*)source.c_str();
		glShaderSource(shader, GL_ONE, &chars, nullptr);

		glCompileShader(shader);

		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::string buffer(maxLength, ' ');
			glGetShaderInfoLog(shader, maxLength, &maxLength, &buffer[0]);

			throw std::runtime_error("Failed to compile shader. " + buffer);
		}
	}
	Shader::~Shader()
	{
		glDeleteShader(shader);
	}

	GLuint Shader::GetShader()
	{
		return shader;
	}
	Shader::Type Shader::GetType()
	{
		return type;
	}
}
