#include <Tide.h>
#include "imgui/imgui.h"
/*
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}
*/

class ExampleLayer : public Tide::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (Tide::Input::IsKeyPressed(TD_KEY_TAB))
		{
			TD_TRACE("Tab key is press (poll) !");
		}
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();
	}

	void OnEvent(Tide::Event& event) override
	{
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
		// PushOverlay(new Tide::ImGuiLayer());
	};
	~TideSandBox() {};
};

Tide::TideApp* Tide::CreateTideApp()
{
	return new TideSandBox();
}