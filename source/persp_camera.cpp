#include <injector_engine.h>

namespace Injector
{
	PerspCamera::PerspCamera(float _fieldOfView, float _aspectRatio, float _nearClipPlane, float _farClipPlane)
	{
		fieldOfView = _fieldOfView;
		aspectRatio = _aspectRatio;
		nearClipPlane = _nearClipPlane;
		farClipPlane = _farClipPlane;
	}

	void PerspCamera::OnFramebufferSize(GLFWwindow* window, int width, int height)
	{
		aspectRatio = float(width) / float(height);

		SetProjMatrixChanged();
		SetViewProjMatrixChanged();
	}
	glm::mat4 PerspCamera::GetProjMatrix()
	{
		if (isProjMatrixChaged)
		{
			projMatrix = glm::perspective<float>(fieldOfView, aspectRatio, nearClipPlane, farClipPlane);
			isProjMatrixChaged = false;
		}

		return projMatrix;
	}
}