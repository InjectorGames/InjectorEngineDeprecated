#include <injector_engine.h>

namespace Injector
{
	DiffuseMaterial::DiffuseMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader, uint16_t renderQueue) :
		Material(vertexShader, fragmentShader, renderQueue),
		mvp(GetUniformLocation("u_MVP")),
		normal(GetUniformLocation("u_Normal")),
		color(GetUniformLocation("u_Color")),
		ambientColor(GetUniformLocation("u_AmbientColor")),
		lightColor(GetUniformLocation("u_LightColor")),
		lightDirection(GetUniformLocation("u_LightDirection"))
	{
		SetColor(glm::vec4(1.0f));
		SetAmbientColor(glm::vec4(0.25f));
		SetLightColor(glm::vec4(1.0f));
		SetLightDirection(glm::vec3(1.0f));
	}

	void DiffuseMaterial::SetMVP(const glm::mat4& value) const
	{
		SetUniform(mvp, value);
	}
	void DiffuseMaterial::SetNormal(const glm::mat3& value) const
	{
		SetUniform(normal, value);
	}
	void DiffuseMaterial::SetColor(const glm::vec4& value) const
	{
		SetUniform(color, value);
	}
	void DiffuseMaterial::SetAmbientColor(const glm::vec4& value) const
	{
		SetUniform(ambientColor, value);
	}
	void DiffuseMaterial::SetLightColor(const glm::vec4& value) const
	{
		SetUniform(lightColor, value);
	}
	void DiffuseMaterial::SetLightDirection(const glm::vec3& value) const
	{
		SetUniform(lightDirection, glm::normalize(value));
	}

	void DiffuseMaterial::OnRender(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		auto window = Engine::GetWindow();
		window->SetDepthTesting(true);
		window->SetStencilTesting(false);
		window->SetColorBlending(false);

		Use();

		for (auto const& drawer : drawers)
		{
			auto model = drawer->GetMatrix();
			SetMVP(viewProj * model);
			SetNormal(glm::transpose(glm::inverse(view * model)));
			drawer->OnDraw();
		}
	}
}