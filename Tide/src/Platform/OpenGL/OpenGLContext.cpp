#include "tdpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

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
		TD_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TD_CORE_ASSERT(status, "Failed to initialze Glad!");

		TD_CORE_INFO("OpenGL Info");
		std::cout << "Vendor " << glGetString(GL_VENDOR) << std::endl; // TD_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		std::cout << "Renderer " << glGetString(GL_RENDERER) << std::endl; // TD_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		std::cout << "Version " << glGetString(GL_VERSION) << std::endl; // TD_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		
	#ifdef TD_ENABLE_ASSERTS
			int versionMajor;
			int versionMinor;
			glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
			glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

			TD_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Tide requires at least OpenGL version 4.5!");
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}