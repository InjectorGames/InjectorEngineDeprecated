#include <injector_engine.h>

namespace Injector
{
	DemoController::DemoController() : Entity("DemoController")
	{
		auto window = Engine::GetWindow();
		window->SetFaceCulling(true);
		window->SetWindingOrder(true);
		window->SetDepthTesting(true);

		camera = std::make_shared<FreeLookCamera>();
		Engine::AddEntity(camera);

		cube = std::make_shared<Renderer>(Engine::GetDiffuseMaterial(), Engine::GetCubeMeshVN());
		cube->Translate(glm::vec3(0.0f, 0.0f, 2.0f));
		cube->SetMatrixChanged();
		Engine::AddEntity(cube);

		editor = std::make_shared<EditorPanel>();
		Engine::AddEntity(editor);
	}

	void DemoController::OnUpdate(double time, double deltaTime)
	{
		cube->Rotate(glm::quat(glm::vec3(deltaTime / 2.0f, deltaTime, 0.0f)));
		cube->SetMatrixChanged();
	}
}
