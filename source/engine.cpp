#include <injector_engine.h>

namespace Injector
{
	bool Engine::isInitialized = false;

	double Engine::time = 0;
	double Engine::lastTime = 0;
	double Engine::deltaTime = 0;

	GLFWwindow* Engine::mainWindow = nullptr;
	std::set<std::shared_ptr<Entity>> Engine::entities = {};

	std::shared_ptr<UnlitMaterial> Engine::unlitMaterial;

	std::shared_ptr<VertMesh> Engine::vertMeshTriangle;
	std::shared_ptr<VertMesh> Engine::vertMeshQuad;

	void Engine::ErrorCallback(int error, const char* description)
	{
		std::cerr << "Engine GLFW error: " << error << ", " << description << std::endl;
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

	bool Engine::IsInitialized()
	{
		return isInitialized;
	}
	void Engine::Initialize()
	{
		if (isInitialized)
			throw std::runtime_error("Failed to initialize injector engine, engine is already initialized.");

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

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to initialize OpenGL context");

		unlitMaterial = std::make_shared<UnlitMaterial>(ReadFromFile("resources/shaders/unlit.vert"), ReadFromFile("resources/shaders/unlit.frag"));

		vertMeshTriangle = VertMesh::CreateTriangle();
		vertMeshQuad = VertMesh::CreateQuad();

		isInitialized = true;

#ifndef NDEBUG
		std::cout << "Initialized injector engine.\n";
#endif
	}
	void Engine::Terminate()
	{
		if (!isInitialized)
			throw std::runtime_error("Failed to terminate injector engine, engine is not initialized.");

		entities.clear();

		unlitMaterial = {};

		vertMeshTriangle = {};
		vertMeshQuad = {};

		if(mainWindow)
			glfwDestroyWindow(mainWindow);

		glfwTerminate();

		isInitialized = false;

#ifndef NDEBUG
		std::cout << "Terminated injector engine.\n";
#endif
	}
	void Engine::Start()
	{
#ifndef NDEBUG
		std::cout << "Started injector engine.\n";
#endif

        while (!glfwWindowShouldClose(mainWindow))
        {
			glClear(GL_COLOR_BUFFER_BIT);

			time = glfwGetTime();
			deltaTime = time - lastTime;

			for (auto const& entity : entities)
				entity->OnUpdate();

			lastTime = time;

            glfwSwapBuffers(mainWindow);
            glfwPollEvents();
        }

#ifndef NDEBUG
		std::cout << "Stopped injector engine.\n";
#endif
	}

	std::string Engine::ReadFromFile(const std::string& filePath)
	{
		std::ifstream ifs(filePath);

		if (!ifs)
			throw std::runtime_error("Failed to open shader file.");

		ifs.seekg(0, std::ios::end);
		size_t size = ifs.tellg();
		std::string buffer(size, ' ');
		ifs.seekg(0);
		ifs.read(&buffer[0], size);
		return buffer;
	}

	double Engine::GetTime()
	{
		return time;
	}
	double Engine::GetLastTime()
	{
		return lastTime;
	}
	double Engine::GetDeltaTime()
	{
		return deltaTime;
	}

	void Engine::AddEntity(std::shared_ptr<Entity> entity)
	{
		if (!entities.emplace(entity).second)
			throw std::runtime_error("Failed to add engine entity");

#ifndef NDEBUG
		std::cout << "Added a new engine entity: " << entity->name << std::endl;
#endif
	}
	void Engine::RemoveEntity(std::shared_ptr<Entity> entity)
	{
		if (entities.erase(entity) == 0)
			throw std::runtime_error("Failed to remove engine entity");

#ifndef NDEBUG
		std::cout << "Removed engine entity: " << entity->name << std::endl;
#endif
	}

	std::shared_ptr<UnlitMaterial> Engine::GetUnlitMaterial()
	{
		return unlitMaterial;
	}

	std::shared_ptr<VertMesh> Engine::GetVertMeshTriangle()
	{
		return vertMeshTriangle;
	}
	std::shared_ptr<VertMesh> Engine::GetVertMeshQuad()
	{
		return vertMeshQuad;
	}

	// TODO: add debug extension load
}
