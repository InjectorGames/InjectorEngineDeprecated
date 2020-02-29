#include <injector_engine.h>

namespace Injector
{
	GLuint Buffer::GenerateBuffer()
	{
		GLuint buffer;
		glGenBuffers(GL_ONE, &buffer);
		return buffer;
	}
	void Buffer::DeleteBuffer(GLuint buffer)
	{
		glDeleteBuffers(GL_ONE, &buffer);
	}

	Buffer::Buffer(Type _type, Usage _usage, GLsizeiptr _size, const GLvoid* data) : buffer(GenerateBuffer()), type(_type)
	{
		usage = _usage;

		BindBuffer();
		SetBufferData(_size, data);
		UnbindBuffer();
	}

	Buffer::~Buffer()
	{
		DeleteBuffer(buffer);
	}

	Buffer::Usage Buffer::GetUsage()
	{
		return usage;
	}
	GLsizeiptr Buffer::GetSize()
	{
		return size;
	}

	void Buffer::BindBuffer() const
	{
		glBindBuffer((GLenum)type, buffer);
	}
	void Buffer::UnbindBuffer() const
	{
		glBindBuffer((GLenum)type, GL_ZERO);
	}

	void Buffer::SetBufferData(GLsizeiptr _size, const GLvoid* data)
	{
		size = _size;
		glBufferData((GLenum)type, _size, data, (GLenum)usage);
	}
	void Buffer::SetBufferData(Usage _usage, GLsizeiptr _size, const GLvoid* data)
	{
		usage = _usage;
		size = _size;
		glBufferData((GLenum)type, _size, data, (GLenum)_usage);
	}

	void Buffer::SetBufferSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data)
	{
		glBufferSubData((GLenum)type, offset, size, data);
	}
}