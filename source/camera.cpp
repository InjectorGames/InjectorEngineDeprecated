#include <injector_engine.h>

namespace Injector
{
	Camera::Camera() : Entity("UntitledCamera"), Transform(glm::vec3(0.0f), glm::quat(glm::vec3(0.0f)), glm::vec3(-1.0f))
	{
		projMatrix = glm::mat4(1.0f);
		viewProjMatrix = glm::mat4(1.0f);

		isProjMatrixChaged = true;
		isViewProjMatrixChaged = true;
	}

	void Camera::SetProjMatrixChanged()
	{
		isProjMatrixChaged = true;
	}
	void Camera::SetViewProjMatrixChanged()
	{
		isViewProjMatrixChaged = true;
	}

	glm::mat4 Camera::GetProjMatrix()
	{
		if (isMatrixChaged)
		{
			projMatrix = glm::mat4(1.0f);
			isProjMatrixChaged = false;
		}

		return projMatrix;
	}
	glm::mat4 Camera::GetViewProjMatrix()
	{
		if (isViewProjMatrixChaged)
		{
			viewProjMatrix = GetProjMatrix() * GetMatrix();
			isViewProjMatrixChaged = false;
		}

		return viewProjMatrix;
	}
}
