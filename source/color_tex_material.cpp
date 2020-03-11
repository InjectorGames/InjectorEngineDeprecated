#include <injector_engine.h>

namespace Injector
{
	ColorTexMaterial::ColorTexMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) : ColorMaterial(vertexShader, fragmentShader), textureMap(GetUniformLocation("u_TextureMap"))
	{
		SetUniform(textureMap, 0);
	}

	void ColorTexMaterial::OnRender(std::shared_ptr<Window> window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		if (texture)
			texture->Activate(0);

		ColorMaterial::OnRender(window, model, view, proj, viewProj);
	}
}
