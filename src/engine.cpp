#include <injector_engine.h>

namespace InjectorEngine
{
	bool isInitialized = false;
	double lastTime = 0;

	GLFWwindow* mainWindow = nullptr;
	std::set<Entity*> entities;

	void ErrorCallback(int error, const char* description)
	{
		std::cerr << "Engine GLFW error: " << error << ", " << description << std::endl;
	}
	void WindowCloseCallback(GLFWwindow* window)
	{
		for (auto const& entity : entities)
			entity->OnWindowClose(window);
	}
	void WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		for (auto const& entity : entities)
			entity->OnWindowResize(window, width, height);
	}
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		//glViewport(0, 0, width, height);

		for (auto const& entity : entities)
			entity->OnFramebufferResize(window, width, height);
	}
	void WindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
	{
		//set_interface_scale(xscale, yscale);

		for (auto const& entity : entities)
			entity->OnWindowContentRescale(window, xscale, yscale);
	}
	void WindowPosCallback(GLFWwindow* window, int xpos, int ypos)
	{
		for (auto const& entity : entities)
			entity->OnWindowReposition(window, xpos, ypos);
	}
	void WindowIconifyCallback(GLFWwindow* window, int iconified)
	{
		//if (iconified)
		//{
			// The window was iconified
		//}
		//else
		//{
			// The window was restored
		//}

		for (auto const& entity : entities)
			entity->OnWindowIconify(window, iconified);
	}
	void WindowMaximizeCallback(GLFWwindow* window, int maximized)
	{
		for (auto const& entity : entities)
			entity->OnWindowMaximize(window, maximized);
	}
	void WindowFocusCallback(GLFWwindow* window, int focused)
	{
		for (auto const& entity : entities)
			entity->OnWindowFocus(window, focused);
	}
	void WindowRefreshCallback(GLFWwindow* window)
	{
		//draw_editor_ui(window);
		//glfwSwapBuffers(window);

		for (auto const& entity : entities)
			entity->OnWindowRefresh(window);
	}


	bool Engine::IsInitialized()
	{
		return isInitialized;
	}
	void Engine::Initialize()
	{
		if (isInitialized)
			throw std::runtime_error("Failedt to initialize injector engine, engine is already initialized.");

		glfwSetErrorCallback(ErrorCallback);

		if (!glfwInit())
			throw std::runtime_error("Failed to intialize GLFW.");

		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

		mainWindow = glfwCreateWindow(640, 480, "My Title", nullptr, nullptr);

		if (!mainWindow)
			throw std::runtime_error("Failed to create GLFW window.");

		glfwSetWindowCloseCallback(mainWindow, WindowCloseCallback);
		glfwSetWindowSizeCallback(mainWindow, WindowSizeCallback);
		glfwSetFramebufferSizeCallback(mainWindow, FramebufferSizeCallback);
		glfwSetWindowContentScaleCallback(mainWindow, WindowContentScaleCallback);
		glfwSetWindowPosCallback(mainWindow, WindowPosCallback);
		glfwSetWindowIconifyCallback(mainWindow, WindowIconifyCallback);
		glfwSetWindowMaximizeCallback(mainWindow, WindowMaximizeCallback);
		glfwSetWindowFocusCallback(mainWindow, WindowFocusCallback);
		glfwSetWindowRefreshCallback(mainWindow, WindowRefreshCallback);

		glfwMakeContextCurrent(mainWindow);

		isInitialized = true;
		std::cout << "Initialized injector engine.\n";
	}
	void Engine::Terminate()
	{
		if (!isInitialized)
			throw std::runtime_error("Failed to terminate injector engine, engine is not initialized.");

		if(mainWindow)
			glfwDestroyWindow(mainWindow);

		glfwTerminate();

		isInitialized = false;
		std::cout << "Terminated injector engine.\n";
	}
	void Engine::Start()
	{
		std::cout << "Started injector engine.\n";

        while (!glfwWindowShouldClose(mainWindow))
        {
			auto currentTime = glfwGetTime();
			auto deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			for (auto const& entity : entities)
				entity->OnUpdate(deltaTime);

            glfwSwapBuffers(mainWindow);
            glfwPollEvents();
        }

		std::cout << "Stopped injector engine.\n";
	}

	void Engine::_AddEntity(Entity* entity)
	{
		entities.emplace(entity);
		std::cout << "Added a new entity: " << entity->name << std::endl;
	}
	void Engine::_RemoveEntity(Entity* entity)
	{
		entities.erase(entity);
		std::cout << "Removed entity: " << entity->name << std::endl;
	}

	// TODO: add debug extension load
}
