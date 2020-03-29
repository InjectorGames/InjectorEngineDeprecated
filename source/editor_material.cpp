#include <injector_engine.h>

namespace Injector
{
	EditorMaterial::EditorMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader, uint16_t renderQueue) :
		Material(vertexShader, fragmentShader, renderQueue),
		model(GetUniformLocation("u_Model")),
		color(GetUniformLocation("u_Color"))
	{
		SetColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.8f));
	}

	void EditorMaterial::SetModel(const glm::mat4& value) const
	{
		SetUniform(model, value);
	}
	void EditorMaterial::SetColor(const glm::vec4& value) const
	{
		SetUniform(color, value);
	}

	void EditorMaterial::OnRender(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		auto window = Engine::GetWindow();
		window->SetDepthTesting(true);
		window->SetStencilTesting(false);
		window->SetColorBlending(true);
		window->SetColorBlendType(Window::BlendType::SrcAlpha, Window::BlendType::OneMinusSrcAlpha);

		Use();

		for (auto const& drawer : drawers)
		{
			SetModel(drawer->GetMatrix());
			drawer->OnDraw();
		}
	}
}
