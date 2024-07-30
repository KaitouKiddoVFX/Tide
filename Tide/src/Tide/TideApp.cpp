#include "tdpch.h"
#include "Input.h"
#include "TideApp.h"
#include "Tide/Log.h"
#include "Tide/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Tide {
#define BIND_EVENT_FN(x) std::bind(&TideApp::x, this, std::placeholders::_1)
	TideApp* TideApp::s_Instance = nullptr;

	TideApp::TideApp()
	{
		TD_CORE_ASSERT(!s_Instance, "TideApp already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void TideApp::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void TideApp::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void TideApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void TideApp::Run()
	{
		while (m_Running)
		{			
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool TideApp::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}