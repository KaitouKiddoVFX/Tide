#pragma once

#include "RenderCommand.h"

namespace Tide
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& verterxArray);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}