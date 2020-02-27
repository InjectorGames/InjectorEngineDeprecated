#include <injector_engine.h>

namespace Injector
{
	const GLfloat Primitive::TriangleVertices[9] =
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
	};
	const GLfloat Primitive::TriangleNormals[9]
	{
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
	};
	const GLbyte Primitive::TriangleIndices[3]
	{
		0, 1, 2,
	};
	const size_t Primitive::TriangleVertexSize = sizeof(TriangleVertices);
	const size_t Primitive::TriangleIndexSize = sizeof(TriangleIndices);

	const GLfloat Primitive::QuadVertices[12] =
	{
		-0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
	};
	const GLfloat Primitive::QuadNormals[12]
	{
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,
	};
	const GLbyte Primitive::QuadIndices[6]
	{
		0, 1, 2, 0, 2, 3,
	};
	const size_t Primitive::QuadVertexSize = sizeof(QuadVertices);
	const size_t Primitive::QuadIndexSize = sizeof(QuadIndices);
}
