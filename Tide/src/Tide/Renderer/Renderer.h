#pragma once

#include "Tide/Renderer/Shader.h"
#include "Tide/Renderer/RenderCommand.h"
#include "Tide/Renderer/OrthographicCamera.h"

namespace Tide
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const Tide::Ref<Shader>& shader, const Tide::Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		
		static SceneData* m_SceneData;
	};
}