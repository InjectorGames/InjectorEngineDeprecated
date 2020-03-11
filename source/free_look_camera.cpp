#include <injector_engine.h>

namespace Injector
{
	void FreeLookCamera::OnUpdate(double time, double deltaTime)
	{
		auto verticalAxis = Engine::GetVerticalAxis();
		auto horizontalAxis = -Engine::GetHorizontalAxis();
		Translate(glm::vec3(horizontalAxis * deltaTime, 0.0f, verticalAxis * deltaTime));
		SetMatrixChanged();
	}
}
