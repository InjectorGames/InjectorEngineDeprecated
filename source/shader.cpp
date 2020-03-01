#include <injector_engine.h>

namespace Injector
{
	Shader::Shader(Type _type, const std::string& source, bool readFromFile) : shader(glCreateShader((GLenum)_type)), type(_type)
	{
		// TODO: get hight opengl version
		std::string code("#version 330\n");

		if (readFromFile)
			code += ReadTextFromFile(source);
		else
			code += source;

		auto chars = (const GLchar*)code.c_str();
		glShaderSource(shader, GL_ONE, &chars, nullptr);

		glCompileShader(shader);

		auto success = (GLint)0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success == GL_FALSE)
		{
			auto maxLength = (GLint)0;
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
}
