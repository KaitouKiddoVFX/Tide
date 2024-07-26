#pragma once
#include "Core.h"
#include "Window.h"
#include "Tide/LayerStack.h"
#include "Tide/Events/Event.h"
#include "Tide/Events/AppEvent.h"
#include "Tide/ImGui/ImGuiLayer.h"
#include "Tide/Renderer/Shader.h"
#include "Tide/Renderer/Buffer.h"
#include "Tide/Renderer/VertexArray.h"
#include "Tide/Renderer/OrthographicCamera.h"

namespace Tide
{
	class TIDE_API TideApp
	{
	public:
		TideApp();
		virtual ~TideApp() = default;
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static TideApp& Get() { return *s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;

	private:
		static TideApp* s_Instance;
	};

	// To be defined in CLIENT
	TideApp* CreateTideApp();
}
