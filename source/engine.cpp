#include <injector_engine.h>

namespace Injector
{
	double Engine::time = 0;
	double Engine::lastTime = 0;
	double Engine::deltaTime = 0;

	float Engine::verticalAxis = 0;
	float Engine::horizontalAxis = 0;

	std::shared_ptr<Window> Engine::window = {};
	std::set<std::shared_ptr<Entity>> Engine::entities = {};

	std::shared_ptr<Mesh> Engine::squareMeshV = {};
	std::shared_ptr<Mesh> Engine::squareMeshVN = {};
	std::shared_ptr<Mesh> Engine::squareMeshVNU = {};
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
	void Engine::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_S)
		{
			if (action == GLFW_PRESS)
				verticalAxis = -1.0f;
			else if (action == GLFW_RELEASE)
				verticalAxis = 0.0f;
		}
		if (key == GLFW_KEY_W)
		{
			if (action == GLFW_PRESS)
				verticalAxis = 1.0f;
			else if (action == GLFW_RELEASE)
				verticalAxis = 0.0f;
		}
		if (key == GLFW_KEY_A)
		{
			if (action == GLFW_PRESS)
				horizontalAxis = -1.0f;
			else if(action == GLFW_RELEASE)
				horizontalAxis = 0.0f;
		}
		if (key == GLFW_KEY_D)
		{
			if (action == GLFW_PRESS)
				horizontalAxis = 1.0f;
			else if (action == GLFW_RELEASE)
				horizontalAxis = 0.0f;
		}

		for (auto const& entity : entities)
			entity->OnKeyCallback(window, key, scancode, action, mods);
	}


	void Engine::Clear()
	{
		// TODO: remove meshes
		cubeMeshVN = {};
		cubeMeshV = {};
		squareMeshVN = {};
		squareMeshV = {};

		entities.clear();
		window = {};
	}

	template<class TVertex, class TIndex>
	std::shared_ptr<Mesh> Engine::CreateMesh(Mesh::DrawMode drawMode, Mesh::IndexType indexType, Buffer::UsageType usage, const std::vector<TVertex>& vertices, const std::vector<TIndex>& indices, const std::vector<Attribute>& attributes)
	{
		auto vertexBuffer = std::make_shared<Buffer>(Buffer::Type::Array, usage, vertices.size() * sizeof(TVertex), &vertices[0]);

		auto indexBuffer = std::make_shared<Buffer>(Buffer::Type::ElementArray, usage, indices.size() * sizeof(TIndex), &indices[0]);

		return std::make_shared<Mesh>(drawMode, indexType, indices.size(), vertexBuffer, indexBuffer, attributes);
	}

	std::shared_ptr<Mesh> Engine::GetSquareMeshV()
	{
		if (!squareMeshV)
		{
			std::vector<Attribute> vertexAttributes = { Attribute(0, Attribute::Size::Three, Attribute::Type::Float, false, 0, 0), };
			squareMeshV = CreateMesh<GLfloat, GLbyte>(Mesh::DrawMode::Triangles, Mesh::IndexType::UnsignedByte, Buffer::UsageType::StaticDraw, Primitive::SquareVertices, Primitive::SquareIndices, vertexAttributes);
		}

		return squareMeshV;
	}
	std::shared_ptr<Mesh> Engine::GetSquareMeshVN()
	{
		if (!squareMeshVN)
		{
			std::vector<Attribute> vertexAttributes =
			{
				Attribute(0, Attribute::Size::Three, Attribute::Type::Float, false, 0, 0),
				Attribute(1, Attribute::Size::Three, Attribute::Type::Float, true, 0, Primitive::SquareVertices.size() * sizeof(GLfloat)),
			};

			auto vertices(Primitive::SquareVertices);
			std::copy(Primitive::SquareNormals.begin(), Primitive::SquareNormals.end(), std::back_inserter(vertices));

			return CreateMesh<GLfloat, GLbyte>(Mesh::DrawMode::Triangles, Mesh::IndexType::UnsignedByte, Buffer::UsageType::StaticDraw, vertices, Primitive::SquareIndices, vertexAttributes);
		}

		return squareMeshVN;
	}
	std::shared_ptr<Mesh> Engine::GetCubeMeshV()
	{
		if (!cubeMeshV)
		{
			std::vector<Attribute> vertexAttributes = { Attribute(0, Attribute::Size::Three, Attribute::Type::Float, false, 0, 0), };
			return CreateMesh<GLfloat, GLbyte>(Mesh::DrawMode::Triangles, Mesh::IndexType::UnsignedByte, Buffer::UsageType::StaticDraw, Primitive::CubeVertices, Primitive::CubeIndices, vertexAttributes);
		}

		return cubeMeshV;
	}
	std::shared_ptr<Mesh> Engine::GetCubeMeshVN()
	{
		if (!cubeMeshVN)
		{
			std::vector<Attribute> vertexAttributes =
			{
				Attribute(0, Attribute::Size::Three, Attribute::Type::Float, false, 0, 0),
				Attribute(1, Attribute::Size::Three, Attribute::Type::Float, true, 0, Primitive::CubeVertices.size() * sizeof(GLfloat)),
			};

			auto vertices(Primitive::CubeVertices);
			std::copy(Primitive::CubeNormals.begin(), Primitive::CubeNormals.end(), std::back_inserter(vertices));

			return CreateMesh<GLfloat, GLbyte>(Mesh::DrawMode::Triangles, Mesh::IndexType::UnsignedByte, Buffer::UsageType::StaticDraw, vertices, Primitive::CubeIndices, vertexAttributes);
		}

		return cubeMeshVN;
	}

	/*std::shared_ptr<Mesh> Mesh::CreateSquareVNU(DrawMode drawMode, Buffer::UsageType usage)
	{
		std::vector<VertexAttribute> vertexAttributes =
		{
			VertexAttribute(0, VertexAttribute::Size::Three, VertexAttribute::Type::Float, false, 0, 0),
			VertexAttribute(1, VertexAttribute::Size::Three, VertexAttribute::Type::Float, true, 0, Primitive::SquareVertices.size() * sizeof(GLfloat)),
			VertexAttribute(2, VertexAttribute::Size::Two, VertexAttribute::Type::Float, true, 0, (Primitive::SquareVertices.size() + Primitive::SquareNormals.size()) * sizeof(GLfloat)),
		};

		auto vertices(Primitive::SquareVertices);
		std::copy(Primitive::SquareNormals.begin(), Primitive::SquareNormals.end(), std::back_inserter(vertices));
		std::copy(Primitive::SquareTexCoords.begin(), Primitive::SquareTexCoords.end(), std::back_inserter(vertices));

		return CreateMesh<GLfloat, GLbyte>(drawMode, IndexType::UnsignedByte, usage, vertices, Primitive::SquareIndices, vertexAttributes);
	}*/

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

	float Engine::GetVerticalAxis()
	{
		return verticalAxis;
	}
	float Engine::GetHorizontalAxis()
	{
		return horizontalAxis;
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
		glfwSetKeyCallback(window->window, KeyCallback);
	}

	void Engine::AddEntity(std::shared_ptr<Entity> entity)
	{
		if (!entities.emplace(entity).second)
			throw std::runtime_error("Failed to add engine entity");
	}
	void Engine::RemoveEntity(std::shared_ptr<Entity> entity)
	{
		if (!entities.erase(entity))
			throw std::runtime_error("Failed to remove engine entity");
	}

	void Engine::StartUpdate()
	{
		auto currentWindow = window;

		while (!glfwWindowShouldClose(currentWindow->window))
		{
			currentWindow->ClearBuffers();

			time = glfwGetTime();
			deltaTime = time - lastTime;

			for (auto const& entity : entities)
				entity->OnUpdate();
			for (auto const& entity : entities)
				entity->OnRender();

			lastTime = time;

			glfwSwapBuffers(currentWindow->window);
			glfwPollEvents();
		}
	}

	// TODO: add debug extension load
}
