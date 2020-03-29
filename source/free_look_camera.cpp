#include <injector_engine.h>

namespace Injector
{
	void FreeLookCamera::OnUpdate()
	{
		auto deltaTime = Engine::GetDeltaTime();
		auto verticalAxis = Engine::GetVerticalAxis();
		auto horizontalAxis = -Engine::GetHorizontalAxis();
		Translate(glm::vec3(horizontalAxis * deltaTime, 0.0f, verticalAxis * deltaTime));
		SetMatrixChanged();
	}
}
