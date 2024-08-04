#include "TideSandBox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

TideSandBox2D::TideSandBox2D()
	: Layer("TideSandBox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void TideSandBox2D::OnAttach()
{
}

void TideSandBox2D::OnDetach()
{
}

void TideSandBox2D::OnUpdate(Tide::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Tide::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Tide::RenderCommand::Clear();
	Tide::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Tide::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Tide::Renderer2D::EndScene();
}

void TideSandBox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void TideSandBox2D::OnEvent(Tide::Event& e)
{
	m_CameraController.OnEvent(e);
}