#include "tdpch.h"
#include "TideApp.h"
#include "Tide/Log.h"
#include <GLFW/glfw3.h>

namespace Tide
{

#define BIND_EVENT_FN(x) std::bind(&TideApp::x, this, std::placeholders::_1)

	TideApp::TideApp()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	};

	TideApp::~TideApp()
	{
	};

	/*
	void TideApp::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void TideApp::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	*/

	void TideApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		TD_CORE_TRACE("{0}", e);
		/*		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if(e.m_Handled)
				break;
		}
		*/
	}

	void TideApp::Run()
	{ 
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//for (Layer* layer : m_LayerStack)
			//	layer->OnUpdate();

			m_Window->OnUpdate();
		}
	};

	bool TideApp::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
