#include "tdpch.h"
#include "Tide/Renderer/GraphicsContext.h"
#include "Tide/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Tide
{
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	TD_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		TD_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}