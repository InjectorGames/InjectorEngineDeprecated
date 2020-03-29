#include <injector_engine.h>

namespace Injector
{
	EditorPanel::EditorPanel(bool isVisible) : Drawer(Engine::GetSquareMeshV(), isVisible)
	{
		aspectRatio = 4.0f / 3.0f;
	}

	glm::mat4 EditorPanel::GetMatrix()
	{
		if (isMatrixChaged)
		{
			auto oneMatrix = glm::mat4(1.0f);
			matrix = glm::translate(oneMatrix, position) * glm::scale(oneMatrix, glm::vec3(scale.x, scale.y * aspectRatio, scale.z)) * glm::mat4_cast(glm::normalize(rotation));
			isMatrixChaged = false;
		}

		return matrix;
	}
}
