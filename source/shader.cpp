#include <injector_engine.h>

namespace Injector
{
	GLuint Shader::CreateShader(Type type)
	{
		return glCreateShader((GLenum)type);
	}
	void Shader::DeleteShader(GLuint shader)
	{
		glDeleteShader(shader);
	}

	Shader::Shader(Type _type, const std::string& source, bool readFromFile) : shader(CreateShader(_type)), type(_type)
	{
		// TODO: get hight opengl version
		std::string code("#version 330\n");

		if (readFromFile)
			code += Engine::ReadTextFromFile(source);
		else
			code += source;

		auto chars = (const GLchar*)code.c_str();
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
		DeleteShader(shader);
	}
}
