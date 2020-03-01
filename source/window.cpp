#include <injector_engine.h>

namespace Injector
{
	GLFWwindow* Window::CreateWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) const
	{
		auto window = glfwCreateWindow(width, height, title.c_str(), monitor, share);

		if (!window)
			throw std::runtime_error("Failed to create GLFW window.");

		return window;
	}

	Window::Window(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) : window(CreateWindow(width, height, title, monitor, share))
	{
		cullFaceFlag = false;
		depthTestFlag = false;
		stencilTestFlag = false;
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

	bool Window::GetCullFaceFlag()
	{
		return cullFaceFlag;
	}
	bool Window::GetDepthTestFlag()
	{
		return depthTestFlag;
	}
	bool Window::GetStencilTestFlag()
	{
		return stencilTestFlag;
	}
}
