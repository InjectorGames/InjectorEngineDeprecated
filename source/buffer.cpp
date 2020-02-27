#include <injector_engine.h>

namespace Injector
{
	Buffer::Buffer(Type _type, Usage _usage, GLsizeiptr _size, const GLvoid* data)
	{
		type = _type;
		usage = _usage;

		glGenBuffers(GL_ONE, &buffer);

		BindBuffer();
		SetBufferData(_size, data);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(GL_ONE, &buffer);
	}

	GLuint Buffer::GetBuffer()
	{
		return buffer;
	}
	Buffer::Type Buffer::GetType()
	{
		return type;
	}
	Buffer::Usage Buffer::GetUsage()
	{
		return usage;
	}
	GLsizeiptr Buffer::GetSize()
	{
		return size;
	}

	void Buffer::BindBuffer()
	{
		glBindBuffer((GLenum)type, buffer);
	}

	void Buffer::SetBufferData(GLsizeiptr _size, const GLvoid* data)
	{
		size = _size;
		glBufferData((GLenum)type, _size, data, (GLenum)usage);
	}
	void Buffer::SetBufferSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
	{
		glBufferSubData((GLenum)type, offset, size, data);
	}
}