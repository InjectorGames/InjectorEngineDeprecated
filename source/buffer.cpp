#include <injector_engine.h>

namespace Injector
{
	GLuint Buffer::Generate()
	{
		GLuint buffer;
		glGenBuffers(GL_ONE, &buffer);
		return buffer;
	}

	Buffer::Buffer(Type _type, UsageType _usage, GLsizeiptr _size, const GLvoid* data) : buffer(Generate()), type(_type)
	{
		usage = _usage;

		Bind();
		SetData(_size, data);
		Unbind();
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(GL_ONE, &buffer);
	}

	Buffer::UsageType Buffer::GetUsage()
	{
		return usage;
	}
	GLsizeiptr Buffer::GetSize()
	{
		return size;
	}

	void Buffer::Bind() const
	{
		glBindBuffer((GLenum)type, buffer);
	}
	void Buffer::Unbind() const
	{
		glBindBuffer((GLenum)type, GL_ZERO);
	}

	void Buffer::SetData(GLsizeiptr _size, const GLvoid* data)
	{
		size = _size;
		glBufferData((GLenum)type, _size, data, (GLenum)usage);
	}
	void Buffer::SetData(UsageType _usage, GLsizeiptr _size, const GLvoid* data)
	{
		usage = _usage;
		size = _size;
		glBufferData((GLenum)type, _size, data, (GLenum)_usage);
	}

	void Buffer::SetSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
	{
		glBufferSubData((GLenum)type, offset, size, data);
	}
}