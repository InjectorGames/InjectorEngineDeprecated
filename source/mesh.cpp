#include <injector_engine.h>

namespace Injector
{
	Mesh::Mesh(DrawMode _drawMode, IndexType _indexType, std::shared_ptr<Buffer> _vertexBuffer, std::shared_ptr<Buffer> _indexBuffer)
	{
		if (_indexType == IndexType::UnsignedByte)
			indexCount = (GLsizei)_indexBuffer->GetSize();
		else if (_indexType == IndexType::UnsignedShort)
			indexCount = (GLsizei)(_indexBuffer->GetSize() / sizeof(GLushort));
		else if (_indexType == IndexType::UnsignedInt)
			indexCount = (GLsizei)(_indexBuffer->GetSize() / sizeof(GLuint));

		drawMode = _drawMode;
		indexType = _indexType;

		vertexBuffer = _vertexBuffer;
		indexBuffer = _indexBuffer;

		BindVertexArray();
		vertexBuffer->BindBuffer();
		indexBuffer->BindBuffer();
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
}