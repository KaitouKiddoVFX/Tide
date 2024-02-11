#include <Tide.h>

class TideSandBox : public Tide::TideApp
{
public:
	TideSandBox() {};
	~TideSandBox() {};
};

Tide::TideApp* Tide::CreateTideApp()
{
	return new TideSandBox();
}