#include <injector_engine.h>

namespace Injector
{
	Editor::Editor(std::shared_ptr<Camera> _camera) :
		camera(_camera),
		material(std::make_shared<EditorMaterial>(std::make_shared<Shader>(Shader::Type::Vertex, "resources/shaders/editor.vert", true), std::make_shared<Shader>(Shader::Type::Fragment, "resources/shaders/editor.frag", true))),
		topPanel(std::make_shared<EditorPanel>())
	{
		camera->AddMaterial(material);
		material->AddDrawer(topPanel);

		topPanel->scale = glm::vec3(1.0f, 1.0f, 1.0f);
		topPanel->SetMatrixChanged();
	}
	Editor::~Editor()
	{
		material->RemoveDrawer(topPanel);
		camera->RemoveMaterial(material);
	}

	void Editor::OnFramebufferSize(GLFWwindow* window, int width, int height)
	{
		auto aspectRatio = float(width) / float(height);
		topPanel->aspectRatio = aspectRatio;
		topPanel->SetMatrixChanged();
	}
}
