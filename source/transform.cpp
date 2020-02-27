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
			matrix = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale) * glm::mat4_cast(glm::normalize(rotation));
			isMatrixChaged = false;
		}

		return matrix;
	}
}
