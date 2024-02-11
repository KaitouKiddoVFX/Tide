#pragma once
#include "Core.h"

namespace Tide
{
	class TIDE_API TideApp
	{
	public:
		TideApp();
		virtual ~TideApp();
		void Run();
	};

	TideApp* CreateTideApp();
}
