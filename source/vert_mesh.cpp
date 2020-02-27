#include <injector_engine.h>

namespace Injector
{
	VertMesh::VertMesh(DrawMode drawMode, IndexType indexType, std::shared_ptr<Buffer> vertexBuffer, std::shared_ptr<Buffer> indexBuffer) : Mesh(drawMode, indexType, vertexBuffer, indexBuffer)
	{
		EnableVertexArrayAttrib(0);
		SetVertexArrayAttribPointer(0, AttribSize::Three, AttribType::Float);
	}

	std::shared_ptr<VertMesh> VertMesh::CreateTriangle(DrawMode drawMode)
	{
		auto vertexBuffer = std::make_shared<Buffer>(Buffer::Type::Array, Buffer::Usage::StaticDraw, Primitive::TriangleVertexSize, Primitive::TriangleVertices);
		auto indexBuffer = std::make_shared<Buffer>(Buffer::Type::ElementArray, Buffer::Usage::StaticDraw, Primitive::TriangleIndexSize, Primitive::TriangleIndices);
		return std::make_shared<VertMesh>(drawMode, IndexType::UnsignedByte, vertexBuffer, indexBuffer);
	}
	std::shared_ptr<VertMesh> VertMesh::CreateQuad(DrawMode drawMode)
	{
		auto vertexBuffer = std::make_shared<Buffer>(Buffer::Type::Array, Buffer::Usage::StaticDraw, Primitive::QuadVertexSize, Primitive::QuadVertices);
		auto indexBuffer = std::make_shared<Buffer>(Buffer::Type::ElementArray, Buffer::Usage::StaticDraw, Primitive::QuadIndexSize, Primitive::QuadIndices);
		return std::make_shared<VertMesh>(drawMode, IndexType::UnsignedByte, vertexBuffer, indexBuffer);
	}
}
