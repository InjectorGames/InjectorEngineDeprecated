#include <injector_engine.h>

namespace Injector
{
	Camera::Camera() :
		Entity("UntitledCamera"),
		Transform(glm::vec3(0.0f), glm::quat(glm::vec3(0.0f)), glm::vec3(-1.0f))
	{
		projMatrix = glm::mat4(1.0f);
		viewProjMatrix = glm::mat4(1.0f);

		isProjMatrixChaged = true;
		isViewProjMatrixChaged = true;
	}

	void Camera::OnRender()
	{
		auto view = GetMatrix();
		auto proj = GetProjMatrix();
		auto viewProj = proj * view;

		std::multiset<Material*, MaterialComparator> sortedMaterials;

		for (auto const& material : materials)
			sortedMaterials.emplace(material.get());
		for (auto material : sortedMaterials)
			material->OnRender(view, proj, viewProj);
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

	void Camera::AddMaterial(std::shared_ptr<Material> material)
	{
		if (!materials.emplace(material).second)
			throw std::runtime_error("Failed to add camera material");
	}
	void Camera::RemoveMaterial(std::shared_ptr<Material> material)
	{
		if (!materials.erase(material))
			throw std::runtime_error("Failed to remove camera material");
	}
}
