#include <injector_engine.h>

namespace Injector
{
	ColorMaterial::ColorMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader, uint16_t renderQueue) :
		Material(vertexShader, fragmentShader, renderQueue),
		mvp(GetUniformLocation("u_MVP")),
		color(GetUniformLocation("u_Color"))
	{
		SetColor(glm::vec4(1.0f));
	}

	void ColorMaterial::SetMVP(const glm::mat4& value) const
	{
		SetUniform(mvp, value);
	}
	void ColorMaterial::SetColor(const glm::vec4& value) const
	{
		SetUniform(color, value);
	}

	void ColorMaterial::OnRender(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		auto window = Engine::GetWindow();
		window->SetDepthTesting(true);
		window->SetStencilTesting(false);
		window->SetColorBlending(false);

		Use();

		for (auto const& drawer : drawers)
		{
			SetMVP(viewProj * drawer->GetMatrix());
			drawer->OnDraw();
		}
	}
}