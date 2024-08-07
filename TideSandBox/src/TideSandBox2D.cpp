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
	Tide::Renderer2D::ResetStats();
	{
		TD_PROFILE_SCOPE("Renderer Prep");
		Tide::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Tide::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		TD_PROFILE_SCOPE("Renderer Draw");
		Tide::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Tide::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0, }, { 0.8f,0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Tide::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Tide::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Tide::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Tide::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, m_CheckerboardTexture, 20.0f);
		Tide::Renderer2D::EndScene();

		Tide::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Tide::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		Tide::Renderer2D::EndScene();
	}
}

void TideSandBox2D::OnImGuiRender()
{
	TD_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	auto stats = Tide::Renderer2D::GetStats();
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void TideSandBox2D::OnEvent(Tide::Event& e)
{
	m_CameraController.OnEvent(e);
}