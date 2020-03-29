#include <injector_engine.h>

namespace Injector
{
	Texture2D::Texture2D(ImageType image, GLint level, InternalFormatType internalFormat, GLsizei width, GLsizei height, FormatType format, PixelType pixel, const GLvoid* data, bool generateMipmap) : Texture(Type::Texture2D)
	{
		if (level != 0 && (image == ImageType::Rectangle || image == ImageType::ProxyRectangle))
			throw std::runtime_error("With this image type level must be 0");

		Bind();

		glTexImage2D((GLenum)image, level, (GLenum)internalFormat, width, height, GL_ZERO, (GLenum)format, (GLenum)pixel, data);

		if(generateMipmap)
			glGenerateMipmap(GL_TEXTURE_2D);

		Unbind();
	}
}
