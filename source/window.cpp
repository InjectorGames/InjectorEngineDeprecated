#include <injector_engine.h>

namespace Injector
{
	GLFWwindow* Window::CreateWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		auto window = glfwCreateWindow(width, height, title.c_str(), monitor, share);

		if (!window)
			throw std::runtime_error("Failed to create GLFW window.");

		return window;
	}

	Window::Window(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) : window(CreateWindow(width, height, title, monitor, share))
	{
		faceCulling = false;
		depthTesting = false;
		stencilTesting = false;
		colorBlending = false;
	}
	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	void Window::SetWindowIcon(const std::vector<GLFWimage>& icons) const
	{
		glfwSetWindowIcon(window, icons.size(), &icons[0]);
	}

	void Window::MakeContextCurrent() const
	{
		glfwMakeContextCurrent(window);
	}
	void Window::DetachContextCurrent()
	{
		glfwMakeContextCurrent(nullptr);
	}

	bool Window::GetFaceCullingFlag()
	{
		return faceCulling;
	}
	bool Window::GetDepthTestFlag()
	{
		return depthTesting;
	}
	bool Window::GetStencilTestFlag()
	{
		return stencilTesting;
	}
	bool Window::GetBlendFlag() 
	{
		return colorBlending;
	}
}
