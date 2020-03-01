#include <injector_engine.h>

namespace Injector
{
	Renderer::Renderer(std::shared_ptr<Material> _material, std::shared_ptr<Mesh> _mesh) : Entity("UntitledRenderer")
	{
		material = _material;
		mesh = _mesh;
	}

	void Renderer::OnRender(double time, double deltaTime, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		// TEMPORARY
		Rotate(glm::quat(glm::vec3(deltaTime / 2.0f, deltaTime, 0.0f)));
		SetMatrixChanged();

		if (material && mesh)
		{
			auto model = GetMatrix();
			material->OnRender(model, view, proj, viewProj);
			mesh->OnRender();
		}
	}
}
