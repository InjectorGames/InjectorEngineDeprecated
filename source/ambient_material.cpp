#include <injector_engine.h>

namespace Injector
{
	AmbientMaterial::AmbientMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) : Material(vertexShader, fragmentShader), mvp(GetUniformLocation("u_MVP")), color(GetUniformLocation("u_Color"))
	{
		SetColor(glm::vec4(1.0f));
	}

	void AmbientMaterial::SetMVP(const glm::mat4& value) const
	{
		SetUniform(mvp, value);
	}
	void AmbientMaterial::SetColor(const glm::vec4& value) const
	{
		SetUniform(color, value);
	}

	void AmbientMaterial::OnRender(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj) const
	{
		Use();
		SetMVP(viewProj * model);
	}
}