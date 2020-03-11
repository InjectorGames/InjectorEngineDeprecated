#include <injector_engine.h>

namespace Injector
{
	ColorMaterial::ColorMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) : Material(vertexShader, fragmentShader), mvp(GetUniformLocation("u_MVP")), color(GetUniformLocation("u_Color"))
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

	void ColorMaterial::OnRender(std::shared_ptr<Window> window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		window->SetDepthTesting(true);
		window->SetStencilTesting(false);
		window->SetColorBlending(false);

		Use();
		SetMVP(viewProj * model);
	}
}