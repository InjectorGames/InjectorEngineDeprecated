#include <injector_engine.h>

namespace Injector
{
	EditorMaterial::EditorMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) : Material(vertexShader, fragmentShader), model(GetUniformLocation("u_Model")), color(GetUniformLocation("u_Color"))
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

	void EditorMaterial::OnRender(std::shared_ptr<Window> window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		window->SetDepthTesting(true);
		window->SetStencilTesting(false);
		window->SetColorBlending(true);
		window->SetColorBlendType(Window::BlendType::SrcAlpha, Window::BlendType::OneMinusSrcAlpha);

		Use();
		SetModel(model);
	}
}
