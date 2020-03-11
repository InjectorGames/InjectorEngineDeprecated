#include <injector_engine.h>

namespace Injector
{
	Renderer::Renderer(std::shared_ptr<Material> _material, std::shared_ptr<Mesh> _mesh, bool _isRenderable) : Entity("UntitledRenderer")
	{
		isRenderable = _isRenderable;
		material = _material;
		mesh = _mesh;
	}

	void Renderer::OnRender(std::shared_ptr<Window> window, double time, double deltaTime, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		if (isRenderable && material && mesh)
		{
			auto model = GetMatrix();
			material->OnRender(window, model, view, proj, viewProj);
			mesh->OnRender();
		}
	}
}
