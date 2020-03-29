#include <injector_engine.h>

namespace Injector
{
	Mesh::Mesh(DrawMode _drawMode, IndexType _indexType, GLsizei _indexCount, std::shared_ptr<Buffer> _vertexBuffer, std::shared_ptr<Buffer> _indexBuffer, const std::vector<Attribute>& attributes) :
		vertexBuffer(_vertexBuffer),
		indexBuffer(_indexBuffer)
	{
		drawMode = _drawMode;
		indexType = _indexType;
		indexCount = _indexCount;

		Bind();
		vertexBuffer->Bind();
		indexBuffer->Bind();

		for (const auto& attribute : attributes)
		{
			attribute.Enable();
			attribute.SetPointer();
		}

		Unbind();
		vertexBuffer->Unbind();
		indexBuffer->Unbind();
	}

	void Mesh::DrawElements()
	{
		glDrawElements((GLenum)drawMode, indexCount, (GLenum)indexType, 0);
	}

	void Mesh::OnDraw()
	{
		Bind();
		DrawElements();
	}
}