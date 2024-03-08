#include <Tide.h>

class ExampleLayer : public Tide::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		TD_INFO("ExampleLayer::Update");
	}

	void OnEvent(Tide::Event& event) override
	{
		TD_TRACE("{0}", event);
	}
};


class TideSandBox : public Tide::TideApp
{
public:
	TideSandBox() 
	{
		PushLayer(new ExampleLayer());
	};
	~TideSandBox() {};
};

Tide::TideApp* Tide::CreateTideApp()
{
	return new TideSandBox();
}