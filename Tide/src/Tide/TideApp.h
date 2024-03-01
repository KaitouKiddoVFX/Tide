#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Tide
{
	class TIDE_API TideApp
	{
	public:
		TideApp();
		virtual ~TideApp();
		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	TideApp* CreateTideApp();
}
