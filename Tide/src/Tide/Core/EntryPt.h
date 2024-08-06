#pragma once

#ifdef TD_PLATFORM_WINDOWS

extern Tide::TideApp* Tide::CreateTideApp();

int main(int argc, char** argv)
{
	Tide::Log::Init();

	TD_PROFILE_BEGIN_SESSION("Startup", "TideProfile-Startup.json");
	auto app = Tide::CreateTideApp();
	TD_PROFILE_END_SESSION();

	TD_PROFILE_BEGIN_SESSION("Startup", "TideProfile-Runtime.json");
	app->Run();
	TD_PROFILE_END_SESSION();

	TD_PROFILE_BEGIN_SESSION("Startup", "TideProfile-Shutdown.json");
	delete app;
	TD_PROFILE_END_SESSION();
}
#endif
