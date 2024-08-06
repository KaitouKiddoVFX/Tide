#include "tdpch.h"
#include "Tide/Core/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Tide
{
	Tide::Ref<spdlog::logger> Log::s_CoreLogger;
	Tide::Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Tide");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
