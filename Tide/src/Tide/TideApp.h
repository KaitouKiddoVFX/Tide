#pragma once
#include "Core.h"
#include "Window.h"
#include "Tide/LayerStack.h"
#include "Tide/Events/Event.h"
#include "Tide/Events/AppEvent.h"

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

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	TideApp* CreateTideApp();
}
