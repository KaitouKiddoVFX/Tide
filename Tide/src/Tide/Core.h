#pragma once

#ifdef TD_PLATFORM_WINDOWS
	#ifdef TD_BUILD_DLL
		#define TIDE_API __declspec(dllexport)
	#else TD_BUILD_DLL
		#define TIDE_API __declspec(dllimport)
	#endif
#else
	#error TD Only support windows!
#endif

#define BIT(x) (1 << x)