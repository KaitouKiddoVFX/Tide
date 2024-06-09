#pragma once
#include "Core.h"
#include "Window.h"
#include "Tide/LayerStack.h"
#include "Tide/Events/Event.h"
#include "Tide/Events/AppEvent.h"
#include "Tide/ImGui/ImGuiLayer.h"

namespace Tide
{
	class TIDE_API TideApp
	{
	public:
		TideApp();
		virtual ~TideApp();
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

		// Temporary
		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

	private:
		static TideApp* s_Instance;
	};

	// To be defined in CLIENT
	TideApp* CreateTideApp();
}
