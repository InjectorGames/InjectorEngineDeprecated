#pragma once
#include <set>
#include <string>
#include <iostream>
#include <stdexcept>
#include <GLFW/glfw3.h>

// Minimum OpenGL Version = 3.1

namespace InjectorEngine
{
	class Entity
	{
	public:
		std::string name;

		Entity();
		Entity(std::string name);

		~Entity();

		virtual void OnUpdate(double deltaTime);
		virtual void OnWindowClose(GLFWwindow* window);
		virtual void OnWindowResize(GLFWwindow* window, int width, int height);
		virtual void OnFramebufferResize(GLFWwindow* window, int width, int height);
		virtual void OnWindowContentRescale(GLFWwindow* window, int width, int height);
		virtual void OnWindowReposition(GLFWwindow* window, int xpos, int ypos);
		virtual void OnWindowIconify(GLFWwindow* window, int iconified);
		virtual void OnWindowMaximize(GLFWwindow* window, int iconified);
		virtual void OnWindowFocus(GLFWwindow* window, int focused);
		virtual void OnWindowRefresh(GLFWwindow* window);
	};

	class Engine
	{
	public:
		static bool IsInitialized();

		static void Initialize();
		static void Terminate();
		
		static void Start();

		static void Engine::_AddEntity(Entity* entity);
		static void Engine::_RemoveEntity(Entity* entity);
	};
}
