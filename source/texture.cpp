#include <injector_engine.h>

namespace Injector
{
	GLuint Texture::Generate()
	{
		GLuint texture;
		glGenTextures(GL_ONE, &texture);
		return texture;
	}

	Texture::Texture(Type _type) : texture(Generate()), type(_type)
	{

	}
	Texture::~Texture()
	{
		glDeleteTextures(GL_ONE, &texture);
	}

	void Texture::Bind() const
	{
		glBindTexture((GLenum)type, texture);
	}
	void Texture::Unbind() const
	{
		glBindTexture((GLenum)type, GL_ZERO);
	}
}
