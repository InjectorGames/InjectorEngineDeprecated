#include <injector_engine.h>

namespace Injector
{
	VertexAttribute::VertexAttribute(GLuint _index, Size _size, Type _type, bool _normalized, GLsizei _stride, GLintptr _offset) : index(_index), size(_size), type(_type), normalized(_normalized), stride(_stride), offset(_offset) {}

	void VertexAttribute::Enable() const
	{
		glEnableVertexAttribArray(index);
	}
	void VertexAttribute::Disable() const
	{
		glDisableVertexAttribArray(index);
	}
	void VertexAttribute::SetPointer() const
	{
		glVertexAttribPointer(index, (GLint)size, (GLenum)type, normalized ? GL_TRUE : GL_FALSE, stride, (const GLvoid*)offset);
	}
}
