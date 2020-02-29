#include <injector_engine.h>

namespace Injector
{
	GLuint VertexArray::GenerateVertexArray()
	{
		GLuint vertexArray;
		glGenVertexArrays(GL_ONE, &vertexArray);
		return vertexArray;
	}
	void VertexArray::DeleteVertexArray(GLuint vertexArray)
	{
		glDeleteVertexArrays(GL_ONE, &vertexArray);
	}

	VertexArray::VertexArray() : vertexArray(GenerateVertexArray()) {}
	VertexArray::~VertexArray() { DeleteVertexArray(vertexArray); }

	void VertexArray::BindVertexArray() const
	{
		glBindVertexArray(vertexArray);
	}
	void VertexArray::UnbindVertexArray()
	{
		glBindVertexArray(GL_ZERO);
	}
}
