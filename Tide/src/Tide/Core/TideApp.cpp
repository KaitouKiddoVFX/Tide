#include "tdpch.h"
#include "Tide/Core/Input.h"
#include "Tide/Core/TideApp.h"
#include "Tide/Core/Log.h"
#include "Tide/Renderer/Renderer.h"

#include <glfw/glfw3.h>

namespace Tide {

	TideApp* TideApp::s_Instance = nullptr;

	TideApp::TideApp()
	{
		TD_PROFILE_FUNCTION();
		TD_CORE_ASSERT(!s_Instance, "TideApp already exists!");
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallback(TD_BIND_EVENT_FN(TideApp::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	TideApp::~TideApp()
	{
		TD_PROFILE_FUNCTION();
		Renderer::Shutdown();
	}

	void TideApp::PushLayer(Layer* layer)
	{
		TD_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void TideApp::PushOverlay(Layer* layer)
	{
		TD_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void TideApp::OnEvent(Event& e)
	{
		TD_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(TD_BIND_EVENT_FN(TideApp::OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(TD_BIND_EVENT_FN(TideApp::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void TideApp::Run()
	{
		TD_PROFILE_FUNCTION();
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

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

	bool TideApp::OnWindowResize(WindowResizeEvent& e)
	{
		TD_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}

}