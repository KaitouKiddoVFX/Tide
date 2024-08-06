#include "TideSandBox2D.h"
#include "ExampleLayer.h"

#include <Tide.h>
#include <Tide/Core/EntryPt.h>

class TideSandBox : public Tide::TideApp
{
public:
	TideSandBox()
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new TideSandBox2D());
	};
	~TideSandBox() {};
};

Tide::TideApp* Tide::CreateTideApp()
{
	return new TideSandBox();
}