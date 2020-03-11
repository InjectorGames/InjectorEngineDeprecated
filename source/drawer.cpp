#include <injector_engine.h>

namespace Injector
{
	Drawer::Drawer(std::shared_ptr<Mesh> _mesh, bool _isVisible)
	{
		mesh = _mesh;
		isVisible = _isVisible;
	}

	bool Drawer::GetIsVisible()
	{
		return isVisible;
	}
	void Drawer::SetIsVisible(bool value)
	{
		isVisible = value;
	}

	void Drawer::OnDraw()
	{
		if (isVisible && mesh)
			mesh->OnDraw();
	}
}
