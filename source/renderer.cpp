#include <injector_engine.h>

namespace Injector
{
	Renderer::Renderer(std::shared_ptr<Material> _material, std::shared_ptr<Mesh> _mesh) : Transform()
	{
		material = _material;
		mesh = _mesh;
	}

	void Renderer::OnRender(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj, const glm::mat4& mvp)
	{
		Rotate(glm::quat(glm::vec3(0.0f, Engine::GetDeltaTime(), 0.0f)));
		SetMatrixChanged();

		if (material && mesh)
		{
			material->OnRender(model, view, proj, viewProj, mvp);
			mesh->OnRender();
		}
	}
}
