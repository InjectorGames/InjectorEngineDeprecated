#include <injector_engine.h>

namespace Injector
{
	double Engine::lastTime = 0;

	std::shared_ptr<Window> Engine::window = {};
	std::set<std::shared_ptr<Entity>> Engine::entities = {};

	std::shared_ptr<AmbientMaterial> Engine::ambientMaterial = {};
	std::shared_ptr<DiffuseMaterial> Engine::diffuseMaterial = {};

	std::shared_ptr<Mesh> Engine::triangleMeshV = {};
	std::shared_ptr<Mesh> Engine::squareMeshV = {};
	std::shared_ptr<Mesh> Engine::cubeMeshV = {};
	std::shared_ptr<Mesh> Engine::cubeMeshVN = {};

	void Engine::ErrorCallback(int error, const char* description)
	{
		std::cerr << "GLFW Error: " << error << ", " << description << std::endl;
	}

	void Engine::WindowCloseCallback(GLFWwindow* window)
	{
		for (auto const& entity : entities)
			entity->OnWindowClose(window);
	}
	void Engine::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		for (auto const& entity : entities)
			entity->OnWindowSize(window, width, height);
	}
	void Engine::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);

		for (auto const& entity : entities)
			entity->OnFramebufferSize(window, width, height);
	}
	void Engine::WindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale)
	{
		//set_interface_scale(xscale, yscale);

		for (auto const& entity : entities)
			entity->OnWindowContentScale(window, xscale, yscale);
	}
	void Engine::WindowPosCallback(GLFWwindow* window, int xpos, int ypos)
	{
		for (auto const& entity : entities)
			entity->OnWindowPosition(window, xpos, ypos);
	}
	void Engine::WindowIconifyCallback(GLFWwindow* window, int iconified)
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
	void Engine::WindowMaximizeCallback(GLFWwindow* window, int maximized)
	{
		for (auto const& entity : entities)
			entity->OnWindowMaximize(window, maximized);
	}
	void Engine::WindowFocusCallback(GLFWwindow* window, int focused)
	{
		for (auto const& entity : entities)
			entity->OnWindowFocus(window, focused);
	}
	void Engine::WindowRefreshCallback(GLFWwindow* window)
	{
		//draw_editor_ui(window);
		//glfwSwapBuffers(window);

		for (auto const& entity : entities)
			entity->OnWindowRefresh(window);
	}

	void Engine::Clear()
	{
		cubeMeshVN = {};
		cubeMeshV = {};
		squareMeshV = {};
		triangleMeshV = {};

		diffuseMaterial = {};
		ambientMaterial = {};

		entities.clear();
		window = {};
	}

	std::shared_ptr<AmbientMaterial> Engine::GetAmbientMaterial()
	{
		return ambientMaterial;
	}
	std::shared_ptr<DiffuseMaterial> Engine::GetDiffuseMaterial()
	{
		return diffuseMaterial;
	}

	std::shared_ptr<Mesh> Engine::GetTriangleMeshV()
	{
		return triangleMeshV;
	}
	std::shared_ptr<Mesh> Engine::GetSquareMeshV()
	{
		return squareMeshV;
	}
	std::shared_ptr<Mesh> Engine::GetCubeMeshV()
	{
		return cubeMeshV;
	}
	std::shared_ptr<Mesh> Engine::GetCubeMeshVN()
	{
		return cubeMeshVN;
	}

	void Engine::Initialize(WindowType windowType)
	{
		glfwSetErrorCallback(ErrorCallback);

		if (!glfwInit())
			throw std::runtime_error("Failed to intialize GLFW.");

		SwitchWindow(windowType);
	}
	void Engine::Terminate()
	{
		Clear();
		glfwTerminate();
	}

	std::shared_ptr<Window> Engine::GetWindow()
	{
		return window;
	}
	void Engine::SwitchWindow(WindowType windowType)
	{
		switch (windowType)
		{
		default:
			throw std::runtime_error("Failed to create window, not supported type");
		case WindowType::OpenGL:
			Clear();

			window = std::make_shared<OpenGLWindow>(800, 600, "Injector Engine (OpenGL)");
			window->MakeContextCurrent();

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				throw std::runtime_error("Failed to initialize OpenGL context");

			ambientMaterial = std::make_shared<AmbientMaterial>(std::make_shared<Shader>(Shader::Type::Vertex, "resources/shaders/ambient.vert", true), std::make_shared<Shader>(Shader::Type::Fragment, "resources/shaders/ambient.frag", true));
			diffuseMaterial = std::make_shared<DiffuseMaterial>(std::make_shared<Shader>(Shader::Type::Vertex, "resources/shaders/diffuse.vert", true), std::make_shared<Shader>(Shader::Type::Fragment, "resources/shaders/diffuse.frag", true));

			triangleMeshV = Mesh::CreateTriangleV();
			squareMeshV = Mesh::CreateSquareV();
			cubeMeshV = Mesh::CreateCubeV();
			cubeMeshVN = Mesh::CreateCubeVN();
			break;
		}

		auto logo16 = Image("resources/images/logo_16.png", 4);
		auto logo32 = Image("resources/images/logo_32.png", 4);
		auto logo48 = Image("resources/images/logo_48.png", 4);
		window->SetWindowIcon(std::vector<GLFWimage>() = { logo16.GetGLFW(), logo32.GetGLFW(), logo48.GetGLFW() });

		glfwSetWindowCloseCallback(window->window, WindowCloseCallback);
		glfwSetWindowSizeCallback(window->window, WindowSizeCallback);
		glfwSetFramebufferSizeCallback(window->window, FramebufferSizeCallback);
		glfwSetWindowContentScaleCallback(window->window, WindowContentScaleCallback);
		glfwSetWindowPosCallback(window->window, WindowPosCallback);
		glfwSetWindowIconifyCallback(window->window, WindowIconifyCallback);
		glfwSetWindowMaximizeCallback(window->window, WindowMaximizeCallback);
		glfwSetWindowFocusCallback(window->window, WindowFocusCallback);
		glfwSetWindowRefreshCallback(window->window, WindowRefreshCallback);
	}

	void Engine::AddEntity(std::shared_ptr<Entity> entity)
	{
		if (!entities.emplace(entity).second)
			throw std::runtime_error("Failed to add entity");
	}
	void Engine::RemoveEntity(std::shared_ptr<Entity> entity)
	{
		if (!entities.erase(entity))
			throw std::runtime_error("Failed to remove entity");
	}

	void Engine::Update()
	{
		while (!glfwWindowShouldClose(window->window))
		{
			window->ClearBuffers();

			auto time = glfwGetTime();
			auto deltaTime = time - lastTime;

			for (auto const& entity : entities)
				entity->OnUpdate(time, deltaTime);

			lastTime = time;

			glfwSwapBuffers(window->window);
			glfwPollEvents();
		}
	}

	// TODO: add debug extension load
}
