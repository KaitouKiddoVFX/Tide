#pragma once

#include "tdpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Tide
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}