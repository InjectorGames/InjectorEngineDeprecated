#include <injector_engine.h>

namespace Injector
{
	bool Engine::isInitialized = false;

	double Engine::time = 0;
	double Engine::lastTime = 0;
	double Engine::deltaTime = 0;

	bool Engine::cullFace = false;
	bool Engine::depthTest = false;

	GLFWwindow* Engine::mainWindow = nullptr;
	std::set<std::shared_ptr<Entity>> Engine::entities = {};

	std::shared_ptr<AmbientMaterial> Engine::ambientMaterial;
	std::shared_ptr<DiffuseMaterial> Engine::diffuseMaterial;

	std::shared_ptr<Mesh> Engine::triangleMeshV;
	std::shared_ptr<Mesh> Engine::squareMeshV;
	std::shared_ptr<Mesh> Engine::cubeMeshV;
	std::shared_ptr<Mesh> Engine::cubeMeshVN;

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

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifndef NDEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#else
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
#endif

		mainWindow = glfwCreateWindow(800, 600, "Injector Engine", nullptr, nullptr);

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

		Image logo16("resources/images/logo_16.png", 4);
		Image logo32("resources/images/logo_32.png", 4);
		Image logo48("resources/images/logo_48.png", 4);

		GLFWimage logos[3]{ logo16.GetGLFW(), logo32.GetGLFW(), logo48.GetGLFW(), };
		glfwSetWindowIcon(mainWindow, 3, logos);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to initialize OpenGL context");

		SetCullFace(true);
		SetDepthTest(true);

		ambientMaterial = std::make_shared<AmbientMaterial>(std::make_shared<Shader>(Shader::Type::Vertex, "resources/shaders/ambient.vert", true), std::make_shared<Shader>(Shader::Type::Fragment, "resources/shaders/ambient.frag", true));
		diffuseMaterial = std::make_shared<DiffuseMaterial>(std::make_shared<Shader>(Shader::Type::Vertex, "resources/shaders/diffuse.vert", true), std::make_shared<Shader>(Shader::Type::Fragment, "resources/shaders/diffuse.frag", true));

		triangleMeshV = Mesh::CreateTriangleV();
		squareMeshV = Mesh::CreateSquareV();
		cubeMeshV = Mesh::CreateCubeV();
		cubeMeshVN = Mesh::CreateCubeVN();

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

		ambientMaterial = {};
		diffuseMaterial = {};

		triangleMeshV = {};
		squareMeshV = {};
		cubeMeshV = {};
		cubeMeshVN = {};

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
			auto clearMask = GL_COLOR_BUFFER_BIT;

			if (depthTest)
				clearMask |= GL_DEPTH_BUFFER_BIT;

			glClear(clearMask);

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

	std::string Engine::ReadTextFromFile(const std::string& filePath)
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

	bool Engine::GetCullFace()
	{
		return cullFace;
	}
	void Engine::SetCullFace(bool value)
	{
		cullFace = value;

		if(value)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}

	bool Engine::GetDepthTest()
	{
		return depthTest;
	}
	void Engine::SetDepthTest(bool value)
	{
		depthTest = value;

		if (value)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
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

	// TODO: add debug extension load
}
