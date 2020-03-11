#include <injector_engine.h>

namespace Injector
{
	Transform::Transform(glm::vec3 _position, glm::quat _rotation, glm::vec3 _scale)
	{
		position = _position;
		rotation = _rotation;
		scale = _scale;
		
		matrix = glm::mat4(1.0f);
		isMatrixChaged = true;
	}

	void Transform::Translate(glm::vec3 offset)
	{
		position += offset;
	}
	void Transform::Rotate(glm::quat offset)
	{
		rotation = offset * rotation;
	}

	void Transform::SetMatrixChanged()
	{
		isMatrixChaged = true;
	}
	glm::mat4 Transform::GetMatrix()
	{
		if (isMatrixChaged)
		{
			auto oneMatrix = glm::mat4(1.0f);
			matrix = glm::translate(oneMatrix, position) * glm::scale(oneMatrix, scale) * glm::mat4_cast(glm::normalize(rotation));
			isMatrixChaged = false;
		}

		return matrix;
	}
}
