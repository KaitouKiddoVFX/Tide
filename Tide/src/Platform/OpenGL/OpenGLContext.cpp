#include "tdpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Tide
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		TD_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TD_CORE_ASSERT(status, "Failed to initialze Glad!");

		// Temporary
		TD_CORE_INFO("OpenGL Info");
		std::cout << "Vendor " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "Version " << glGetString(GL_VERSION) << std::endl;
		// TD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		// TD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		// TD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}