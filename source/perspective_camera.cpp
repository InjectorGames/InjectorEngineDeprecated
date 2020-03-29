#include <injector_engine.h>

namespace Injector
{
	PerspectiveCamera::PerspectiveCamera(float _fieldOfView, float _aspectRatio, float _nearClipPlane, float _farClipPlane)
	{
		fieldOfView = _fieldOfView;
		aspectRatio = _aspectRatio;
		nearClipPlane = _nearClipPlane;
		farClipPlane = _farClipPlane;
	}

	void PerspectiveCamera::OnFramebufferSize(GLFWwindow* window, int width, int height)
	{
		if (width > 0 && height > 0)
		{
			aspectRatio = float(width) / float(height);

			SetProjMatrixChanged();
			SetViewProjMatrixChanged();
		}
	}
	glm::mat4 PerspectiveCamera::GetProjMatrix()
	{
		if (isProjMatrixChaged)
		{
			projMatrix = glm::perspective<float>(fieldOfView, aspectRatio, nearClipPlane, farClipPlane);
			isProjMatrixChaged = false;
		}

		return projMatrix;
	}
}