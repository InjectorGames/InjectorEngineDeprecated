#include <injector_engine.h>

namespace Injector
{
	Entity::Entity(std::string _name)
	{
		name = _name;
	}

	void Entity::OnUpdate() {}
	void Entity::OnWindowClose(GLFWwindow* window) {}
	void Entity::OnWindowSize(GLFWwindow* window, int width, int height) {}
	void Entity::OnFramebufferSize(GLFWwindow* window, int width, int height) {}
	void Entity::OnWindowContentScale(GLFWwindow* window, float xscale, float yscale) {}
	void Entity::OnWindowPosition(GLFWwindow* window, int xpos, int ypos) {}
	void Entity::OnWindowIconify(GLFWwindow* window, int iconified) {}
	void Entity::OnWindowMaximize(GLFWwindow* window, int iconified) {}
	void Entity::OnWindowFocus(GLFWwindow* window, int focused) {}
	void Entity::OnWindowRefresh(GLFWwindow* window) {}
}
