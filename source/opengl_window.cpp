#include <injector_engine.h>

namespace Injector
{
	GLFWwindow* OpenGLWindow::CreateWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share)
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

	GLenum OpenGLWindow::BlendTypeToEnum(BlendType type)
	{
		switch (type)
		{
		default:
			throw std::runtime_error("Unknown blend type");
		case BlendType::Zero:
			return GL_ZERO;
		case BlendType::One:
			return GL_ONE;
		case BlendType::SrcColor:
			return GL_SRC_COLOR;
		case BlendType::OneMinusSrcColor:
			return GL_ONE_MINUS_SRC_COLOR;
		case BlendType::DstColor:
			return GL_DST_COLOR;
		case BlendType::OneMinusDstColor:
			return GL_ONE_MINUS_DST_COLOR;
		case BlendType::SrcAlpha:
			return GL_SRC_ALPHA;
		case BlendType::OneMinusSrcAlpha:
			return GL_ONE_MINUS_SRC_ALPHA;
		case BlendType::DstAlpha:
			return GL_DST_ALPHA;
		case BlendType::OneMinusDstAlpha:
			return GL_ONE_MINUS_DST_ALPHA;
		case BlendType::ConstColor:
			return GL_CONSTANT_COLOR;
		case BlendType::OneMinusConstColor:
			return GL_ONE_MINUS_CONSTANT_COLOR;
		case BlendType::ConstAlpha:
			return GL_CONSTANT_ALPHA;
		case BlendType::OneMinusConstAlpha:
			return GL_ONE_MINUS_CONSTANT_ALPHA;
		case BlendType::SrcAlphaSaturate:
			return GL_SRC_ALPHA_SATURATE;
		case BlendType::Src1Color:
			return GL_SRC1_COLOR;
		case BlendType::OneMinusSrc1Color:
			return GL_ONE_MINUS_SRC1_COLOR;
		case BlendType::Src1Alpha:
			return GL_SRC1_ALPHA;
		case BlendType::OneMinusSrc1Alpha:
			return GL_ONE_MINUS_SRC1_ALPHA;
		}
	}
	
	void OpenGLWindow::ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLWindow::SetWindingOrder(bool clockwise)
	{
		if (windigOrder == clockwise)
			return;

		windigOrder = clockwise;

		if (clockwise)
			glFrontFace(GL_CW);
		else
			glFrontFace(GL_CCW);
	}
	void OpenGLWindow::SetFaceCulling(bool value)
	{
		if (faceCulling == value)
			return;

		faceCulling = value;

		if (value)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}
	void OpenGLWindow::SetDepthTesting(bool value)
	{
		if (depthTesting == value)
			return;

		depthTesting = value;

		if (value)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}
	void OpenGLWindow::SetStencilTesting(bool value)
	{
		if (stencilTesting == value)
			return;

		stencilTesting = value;

		if (value)
			glEnable(GL_STENCIL_TEST);
		else
			glDisable(GL_STENCIL_TEST);
	}
	void OpenGLWindow::SetColorBlending(bool value)
	{
		if (colorBlending == value)
			return;

		colorBlending = value;

		if (value)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}

	void OpenGLWindow::SetFaceCullType(CullType type)
	{
		if (type == CullType::Front)
			glCullFace(GL_FRONT);
		else if (type == CullType::Back)
			glCullFace(GL_BACK);
		else if (type == CullType::Both)
			glCullFace(GL_FRONT_AND_BACK);
		else
			throw std::runtime_error("Unknown face culling type.");
		
	}
	void OpenGLWindow::SetColorBlendType(BlendType source, BlendType destination)
	{
		glBlendFunc(BlendTypeToEnum(source), BlendTypeToEnum(destination));
	}
	void OpenGLWindow::SetColorBlendType(BlendType sourceColor, BlendType destinationColor, BlendType sourceAlpha, BlendType destinationAlpha)
	{
		glBlendFuncSeparate(BlendTypeToEnum(sourceColor), BlendTypeToEnum(destinationColor), BlendTypeToEnum(sourceAlpha), BlendTypeToEnum(destinationAlpha));
	}

}
