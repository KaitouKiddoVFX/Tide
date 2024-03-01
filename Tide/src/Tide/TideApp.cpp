#include "tdpch.h"
#include "TideApp.h"
#include "Tide/Events/AppEvent.h"
#include "Tide/Log.h"
#include <GLFW/glfw3.h>

namespace Tide
{
	TideApp::TideApp()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	};

	TideApp::~TideApp()
	{
	};

	void TideApp::Run()
	{ 
		while (m_Running)
		{
			//glClearColor(1, 0, 1, 1);
			//glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	};
}
