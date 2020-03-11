#include <injector_engine.h>

namespace Injector
{
	ColorTexMaterial::ColorTexMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader, uint16_t renderQueue) :
		ColorMaterial(vertexShader, fragmentShader ,renderQueue),
		textureMap(GetUniformLocation("u_TextureMap"))
	{
		SetUniform(textureMap, 0);
	}

	void ColorTexMaterial::OnRender(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj)
	{
		if (texture)
			texture->Activate(0);

		ColorMaterial::OnRender(view, proj, viewProj);
	}
}
