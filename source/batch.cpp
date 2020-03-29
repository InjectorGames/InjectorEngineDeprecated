#include <injector_engine.h>

namespace Injector
{
	GLuint Batch::Generate()
	{
		GLuint vertexArray;
		glGenVertexArrays(GL_ONE, &vertexArray);
		return vertexArray;
	}

	Batch::Batch() :
		vertexArray(Generate())
	{}
	Batch::~Batch()
	{
		glDeleteVertexArrays(GL_ONE, &vertexArray);
	}

	void Batch::Bind() const
	{
		glBindVertexArray(vertexArray);
	}
	void Batch::Unbind()
	{
		glBindVertexArray(GL_ZERO);
	}
}
