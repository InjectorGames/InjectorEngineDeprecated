#include <injector_engine.h>

namespace Injector
{
	Camera::Camera() : Transform(glm::vec3(0.0f, 0.0f, -2.0f)), Entity("UntitledCamera")
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

	glm::mat4 Camera::GetMatrix()
	{
		if (isMatrixChaged)
		{
			matrix = glm::translate(glm::mat4_cast(glm::normalize(rotation)), position);
			isMatrixChaged = false;
		}

		return matrix;
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

	void Camera::OnUpdate(double time, double deltaTime)
	{
		auto view = GetMatrix();
		auto proj = GetProjMatrix();
		auto viewProj = proj * view;

		for (const auto& renderer : renderers)
			renderer->OnRender(time, deltaTime, view, proj, viewProj);
	}

	void Camera::AddRenderer(std::shared_ptr<Renderer> renderer)
	{
		renderers.emplace(renderer);

#ifndef NDEBUG
		std::cout << "Added camera renderer: " << renderer->name << std::endl;
#endif
	}
	void Camera::RemoveRenderer(std::shared_ptr<Renderer> renderer)
	{
		if (renderers.erase(renderer) == 0)
			throw std::runtime_error("Failed to remove camera renderer");

#ifndef NDEBUG
		std::cout << "Removed camera renderer: " << renderer->name << std::endl;
#endif
	}
}
