#include <injector_engine.h>

namespace Injector
{
	GLFWwindow* OpenGLWindow::CreateWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) const
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifndef NDEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#else
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
#endif

		return Window::CreateWindow(width, height, title, monitor, share);
	}

	OpenGLWindow::OpenGLWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) : Window(width, height, title, monitor, share) {}
	
	void OpenGLWindow::SetCullFaceFlag(bool value)
	{
		if (cullFaceFlag == value)
			return;

		cullFaceFlag = value;

		if (value)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}
	void OpenGLWindow::SetDepthTestFlag(bool value)
	{
		if (depthTestFlag == value)
			return;

		depthTestFlag = value;

		if (value)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}
	void OpenGLWindow::SetStencilTestFlag(bool value)
	{
		if (stencilTestFlag == value)
			return;

		stencilTestFlag = value;

		if (value)
			glEnable(GL_STENCIL_TEST);
		else
			glDisable(GL_STENCIL_TEST);
	}

	void OpenGLWindow::ClearBuffers()
	{
		auto clearMask = GL_COLOR_BUFFER_BIT;

		if (depthTestFlag)
			clearMask |= GL_DEPTH_BUFFER_BIT;
		if (stencilTestFlag)
			clearMask != GL_STENCIL_BUFFER_BIT;

		glClear(clearMask);
	}
}
