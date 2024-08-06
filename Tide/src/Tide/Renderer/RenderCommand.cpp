#pragma once

#include "tdpch.h"
#include "Tide/Renderer/RenderCommand.h"

namespace Tide
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}