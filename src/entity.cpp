#include <injector_engine.h>

namespace InjectorEngine
{
	Entity::Entity()
	{
		name = std::to_string((size_t)this);
		Engine::_AddEntity(this);
	}
	Entity::Entity(std::string _name)
	{
		name = _name;
		Engine::_AddEntity(this);
	}

	Entity::~Entity()
	{
		Engine::_RemoveEntity(this);
	}

	void Entity::OnUpdate(double deltaTime) {}
	void Entity::OnWindowClose(GLFWwindow* window) {}
	void Entity::OnWindowResize(GLFWwindow* window, int width, int height) {}
	void Entity::OnFramebufferResize(GLFWwindow* window, int width, int height) {}
	void Entity::OnWindowContentRescale(GLFWwindow* window, int width, int height) {}
	void Entity::OnWindowReposition(GLFWwindow* window, int xpos, int ypos) {}
	void Entity::OnWindowIconify(GLFWwindow* window, int iconified) {}
	void Entity::OnWindowMaximize(GLFWwindow* window, int iconified) {}
	void Entity::OnWindowFocus(GLFWwindow* window, int focused) {}
	void Entity::OnWindowRefresh(GLFWwindow* window) {}

}
