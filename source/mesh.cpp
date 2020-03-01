#include <injector_engine.h>

namespace Injector
{
	Mesh::Mesh(DrawMode _drawMode, IndexType _indexType, GLsizei _indexCount, std::shared_ptr<Buffer> _vertexBuffer, std::shared_ptr<Buffer> _indexBuffer, const std::vector<VertexAttribute>& vertexAttributes) : vertexBuffer(_vertexBuffer), indexBuffer(_indexBuffer)
	{
		drawMode = _drawMode;
		indexType = _indexType;
		indexCount = _indexCount;

		BindVertexArray();
		vertexBuffer->BindBuffer();
		indexBuffer->BindBuffer();

		for (const auto& attribute : vertexAttributes)
		{
			attribute.Enable();
			attribute.SetPointer();
		}

		UnbindVertexArray();
		vertexBuffer->UnbindBuffer();
		indexBuffer->UnbindBuffer();
	}

	void Mesh::DrawElements()
	{
		glDrawElements((GLenum)drawMode, indexCount, (GLenum)indexType, 0);
	}

	void Mesh::OnRender()
	{
		BindVertexArray();
		DrawElements();
	}

	template<class TVertex, class TIndex>
	std::shared_ptr<Mesh> Mesh::Create(DrawMode drawMode, IndexType indexType, Buffer::Usage usage, const std::vector<TVertex>& vertices, const std::vector<TIndex>& indices, const std::vector<VertexAttribute>& vertexAttributes)
	{
		auto vertexBuffer = std::make_shared<Buffer>(Buffer::Type::Array, usage, vertices.size() * sizeof(TVertex), &vertices[0]);

		auto indexBuffer = std::make_shared<Buffer>(Buffer::Type::ElementArray, usage, indices.size() * sizeof(TIndex), &indices[0]);

		return std::make_shared<Mesh>(drawMode, indexType, indices.size(), vertexBuffer, indexBuffer, vertexAttributes);
	}

	std::shared_ptr<Mesh> Mesh::CreateTriangleV(DrawMode drawMode, Buffer::Usage usage)
	{
		std::vector<VertexAttribute> vertexAttributes = { VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, false, 0, 0), };
		return Create<GLfloat, GLbyte>(drawMode, IndexType::UnsignedByte, usage, Primitive::TriangleVertices, Primitive::TriangleIndices, vertexAttributes);
	}
	std::shared_ptr<Mesh> Mesh::CreateSquareV(DrawMode drawMode, Buffer::Usage usage)
	{
		std::vector<VertexAttribute> vertexAttributes = { VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, false, 0, 0), };
		return Create<GLfloat, GLbyte>(drawMode, IndexType::UnsignedByte, usage, Primitive::SquareVertices, Primitive::SquareIndices, vertexAttributes);
	}
	std::shared_ptr<Mesh> Mesh::CreateCubeV(DrawMode drawMode, Buffer::Usage usage)
	{
		std::vector<VertexAttribute> vertexAttributes = { VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, false, 0, 0), };
		return Create<GLfloat, GLbyte>(drawMode, IndexType::UnsignedByte, usage, Primitive::CubeVertices, Primitive::CubeIndices, vertexAttributes);
	}

	std::shared_ptr<Mesh> Mesh::CreateTriangleVN(DrawMode drawMode, Buffer::Usage usage)
	{
		std::vector<VertexAttribute> vertexAttributes =
		{
			VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, false, 0, 0),
			VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, true, 0, 0),
		};

		return Create<GLfloat, GLbyte>(drawMode, IndexType::UnsignedByte, usage, Primitive::TriangleVertices, Primitive::TriangleIndices, vertexAttributes);
	}
	std::shared_ptr<Mesh> Mesh::CreateSquareVN(DrawMode drawMode, Buffer::Usage usage)
	{
		std::vector<VertexAttribute> vertexAttributes =
		{
			VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, false, 0, 0),
			VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, true, 0, 0),
		};

		return Create<GLfloat, GLbyte>(drawMode, IndexType::UnsignedByte, usage, Primitive::SquareVertices, Primitive::SquareIndices, vertexAttributes);
	}
	std::shared_ptr<Mesh> Mesh::CreateCubeVN(DrawMode drawMode, Buffer::Usage usage)
	{
		std::vector<VertexAttribute> vertexAttributes =
		{
			VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, false, 0, 0),
			VertexAttribute(1, VertexAttribute::Size::Three, VertexAttribute::Type::Float, true, 0, Primitive::CubeVertices.size() * sizeof(GLfloat)),
		};

		auto vertices(Primitive::CubeVertices);
		std::copy(Primitive::CubeNormals.begin(), Primitive::CubeNormals.end(), std::back_inserter(vertices));

		return Create<GLfloat, GLbyte>(drawMode, IndexType::UnsignedByte, usage, vertices, Primitive::CubeIndices, vertexAttributes);
	}
}