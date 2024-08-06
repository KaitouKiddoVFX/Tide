#include "TideSandBox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

TideSandBox2D::TideSandBox2D()
	: Layer("TideSandBox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void TideSandBox2D::OnAttach()
{
	TD_PROFILE_FUNCTION();
	m_CheckerboardTexture = Tide::Texture2D::Create("assets/textures/Checkerboard.png");
}

void TideSandBox2D::OnDetach()
{
	TD_PROFILE_FUNCTION();
}

void TideSandBox2D::OnUpdate(Tide::Timestep ts)
{
	TD_PROFILE_FUNCTION();

	// Update
	{
		TD_PROFILE_SCOPE("CamerController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		TD_PROFILE_SCOPE("Renderer Prep");
		Tide::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Tide::RenderCommand::Clear();
	}

	{
		TD_PROFILE_SCOPE("Renderer Draw");
		Tide::Renderer2D::BeginScene(m_CameraController.GetCamera());
		// Tide::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0, }, { 0.8f,0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Tide::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Tide::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		// Tide::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Tide::Renderer2D::EndScene();
	}
}

void TideSandBox2D::OnImGuiRender()
{
	TD_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void TideSandBox2D::OnEvent(Tide::Event& e)
{
	m_CameraController.OnEvent(e);
}