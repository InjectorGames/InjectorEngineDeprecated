#include <injector_engine.h>

namespace Injector
{
	GLuint Texture::Generate()
	{
		GLuint texture;
		glGenTextures(GL_ONE, &texture);
		return texture;
	}

	Texture::Texture(Type _type) :
		texture(Generate()),
		type(_type)
	{}
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

	void Texture::Activate(GLint index) const
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture((GLenum)type, texture);
	}

	// TODO: add this \/

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
