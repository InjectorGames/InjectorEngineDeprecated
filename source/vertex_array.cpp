#include <injector_engine.h>

namespace Injector
{
	GLuint VertexArray::Generate()
	{
		GLuint vertexArray;
		glGenVertexArrays(GL_ONE, &vertexArray);
		return vertexArray;
	}

	VertexArray::VertexArray() : vertexArray(Generate()) {}
	VertexArray::~VertexArray() { glDeleteVertexArrays(GL_ONE, &vertexArray); }

	void VertexArray::Bind() const
	{
		glBindVertexArray(vertexArray);
	}
	void VertexArray::Unbind()
	{
		glBindVertexArray(GL_ZERO);
	}
}
