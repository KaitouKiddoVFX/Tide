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
		if (Tide::Input::IsKeyPressed(TD_KEY_TAB))
		{
			TD_TRACE("Tab key is press (poll) !");
		}
	}

	void OnEvent(Tide::Event& event) override
	{
		TD_TRACE("{0}", event);
		if (event.GetEventType() == Tide::EventType::KeyPressed)
		{
			Tide::KeyPressedEvent& e = (Tide::KeyPressedEvent&)event;
			if (e.GetKeyCode() == TD_KEY_TAB)
				TD_TRACE("Tab key is pressed (event) !");
			TD_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class TideSandBox : public Tide::TideApp
{
public:
	TideSandBox() 
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Tide::ImGuiLayer());
	};
	~TideSandBox() {};
};

Tide::TideApp* Tide::CreateTideApp()
{
	return new TideSandBox();
}