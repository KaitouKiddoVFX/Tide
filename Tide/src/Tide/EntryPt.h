#pragma once

#ifdef TD_PLATFORM_WINDOWS

extern Tide::TideApp* Tide::CreateTideApp();

int main(int argc, char** argv)
{
	//printf("break");
	Tide::Log::Init();
	TD_CORE_WARN("Initialized Log!");
	int a = 5;
	TD_INFO("Hello! Var={0}", a);

	auto app = Tide::CreateTideApp();
	app->Run();
	delete app;
}
#endif
