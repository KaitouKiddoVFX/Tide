#pragma once

#ifdef TD_PLATFORM_WINDOWS

extern Tide::TideApp* Tide::CreateTideApp();

int main(int argc, char** argv)
{
	printf("break");
	auto app = Tide::CreateTideApp();
	app->Run();
	delete app;
}
#endif
