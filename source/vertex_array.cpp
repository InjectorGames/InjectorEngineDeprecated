#include <injector_engine.h>

namespace Injector
{
	void VertexArray::EnableVertexArrayAttrib(GLuint index)
	{
		glEnableVertexAttribArray(index);
	}
	void VertexArray::DisableVertexArrayAttrib(GLuint index)
	{
		glDisableVertexAttribArray(index);
	}

	void VertexArray::SetVertexArrayAttribPointer(GLuint index, AttribSize size, AttribType type, bool normalized, GLsizei stride, const GLvoid* pointer)
	{
		glVertexAttribPointer(index, (GLint)size, (GLenum)type, normalized ? GL_TRUE : GL_FALSE, stride, pointer);
	}

	VertexArray::VertexArray()
	{
		glGenVertexArrays(GL_ONE, &vertexArray);
	}
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(GL_ONE, &vertexArray);
	}

	GLuint VertexArray::GetVertexArray()
	{
		return vertexArray;
	}
	void VertexArray::BindVertexArray()
	{
		glBindVertexArray(vertexArray);
	}
}
