#include <injector_engine.h>

namespace Injector
{
	Demo::Demo() :
		Entity("Demo"),
		camera(std::make_shared<FreeLookCamera>()),
		editor(std::make_shared<Editor>(camera)),
		diffuseMaterial(std::make_shared<DiffuseMaterial>(std::make_shared<Shader>(Shader::Type::Vertex, "resources/shaders/diffuse.vert", true), std::make_shared<Shader>(Shader::Type::Fragment, "resources/shaders/diffuse.frag", true))),
		cubeDrawer(std::make_shared<Drawer>(Engine::GetCubeMeshVN()))
	{
		Engine::AddEntity(camera);
		Engine::AddEntity(editor);

		camera->AddMaterial(diffuseMaterial);
		diffuseMaterial->AddDrawer(cubeDrawer);

		cubeDrawer->Translate(glm::vec3(0.0f, 0.0f, 2.0f));
		cubeDrawer->SetMatrixChanged();

		auto window = Engine::GetWindow();
		window->SetFaceCulling(true);
		window->SetWindingOrder(true);
	}
	Demo::~Demo()
	{
		diffuseMaterial->RemoveDrawer(cubeDrawer);
		camera->RemoveMaterial(diffuseMaterial);;
	}

	void Demo::OnUpdate()
	{
		auto deltaTime = Engine::GetDeltaTime();
		cubeDrawer->Rotate(glm::quat(glm::vec3(deltaTime / 2.0f, deltaTime, 0.0f)));
		cubeDrawer->SetMatrixChanged();
	}
}
