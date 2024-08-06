#pragma once
#include "Tide/Core/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Tide
{
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Log Macros
#define TD_CORE_TRACE(...)	::Tide::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TD_CORE_INFO(...)	::Tide::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TD_CORE_WARN(...)	::Tide::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TD_CORE_ERROR(...)	::Tide::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TD_CORE_CRITICAL(...)	::Tide::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client Log Marcos
#define TD_TRACE(...)		::Tide::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TD_INFO(...)		::Tide::Log::GetClientLogger()->info(__VA_ARGS__)
#define TD_WARN(...)		::Tide::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TD_ERROR(...)		::Tide::Log::GetClientLogger()->error(__VA_ARGS__)
#define TD_CRITICAL(...)		::Tide::Log::GetClientLogger()->critical(__VA_ARGS__)