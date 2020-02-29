#include <injector_engine.h>

namespace Injector
{
	AmbientMaterial::AmbientMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) : Material(vertexShader, fragmentShader), mvp(GetUniform("u_MVP")), color(GetUniform("u_Color"))
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
		UseProgram();
		SetMVP(viewProj * model);
	}
}