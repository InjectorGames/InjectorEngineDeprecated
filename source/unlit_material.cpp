#include <injector_engine.h>

namespace Injector
{
	UnlitMaterial::UnlitMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
	{
		auto vertex = vertexShader->GetShader();
		auto fragment = fragmentShader->GetShader();

		AttachShader(vertex);
		AttachShader(fragment);

		LinkProgram();

		DetachShader(vertex);
		DetachShader(fragment);

		mvpLocation = GetUniformLocation("u_MVP");
		colorLocation = GetUniformLocation("u_Color");

		SetColor(glm::vec4(1.0f));
	}
	UnlitMaterial::UnlitMaterial(const std::string& vertexSource, const std::string& fragmentSource)
	{
		auto vertexShader = Shader(Shader::Type::Vertex, vertexSource);
		auto fragmentShader = Shader(Shader::Type::Fragment, fragmentSource);
		auto vertex = vertexShader.GetShader();
		auto fragment = fragmentShader.GetShader();

		AttachShader(vertex);
		AttachShader(fragment);

		LinkProgram();

		DetachShader(vertex);
		DetachShader(fragment);

		mvpLocation = GetUniformLocation("u_MVP");
		colorLocation = GetUniformLocation("u_Color");

		UseProgram();
		SetColor(glm::vec4(1.0f));
	}

	GLint UnlitMaterial::GetMVPLocation()
	{
		return mvpLocation;
	}
	void UnlitMaterial::SetMVP(const glm::mat4& value)
	{
		SetUniform(mvpLocation, value);
	}

	GLint UnlitMaterial::GetColorLocation()
	{
		return colorLocation;
	}
	void UnlitMaterial::SetColor(const glm::vec4& value)
	{
		SetUniform(colorLocation, value);
	}

	void UnlitMaterial::OnRender(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj, const glm::mat4& mvp)
	{
		UseProgram();
		SetMVP(mvp);
	}
}