#pragma once
#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64 */
		#define  TD_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#endif

// DLL Support
#ifdef TD_PLATFORM_WINDOWS
	#if TD_DYNAMIC_LINK
		#ifdef TD_BUILD_DLL
			#define TIDE_API __declspec(dllexport)
		#else TD_BUILD_DLL
			#define TIDE_API __declspec(dllimport)
		#endif
	#else
		#define TIDE_API
	#endif
#else
	#error TD Only support windows!
#endif

#ifdef TD_DEBUG
	#define TD_ENABLE_ASSERTS
#endif

#ifdef TD_ENABLE_ASSERTS
	#define TD_ASSERT(x, ...) { if(!(x)) {TD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TD_CORE_ASSERT(x, ...) { if(!(x)) { TD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TD_ASSERT(x, ...)
	#define TD_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define TD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Tide
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> Create(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}