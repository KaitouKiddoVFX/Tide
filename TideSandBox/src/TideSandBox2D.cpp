#include "TideSandBox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

TideSandBox2D::TideSandBox2D()
	: Layer("TideSandBox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void TideSandBox2D::OnAttach()
{
	TD_PROFILE_FUNCTION();
	m_CheckerboardTexture = Tide::Texture2D::Create("assets/textures/Checkerboard.png");
	m_SpriteSheet = Tide::Texture2D::Create("assets/games/textures/RPGpack_sheet_2X.png");
	m_TextureStair = Tide::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 7, 6 }, { 128, 128 });
	m_TextureBush = Tide::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 2, 3 }, { 128, 128 });
	m_TextureTree = Tide::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 4, 1 }, { 128, 128 }, { 1,2 });

	// Init Particle here
	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
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

#if 0
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
#endif

	// the position of cursor convert into worldspace
	if (Tide::Input::IsMouseButtonPressed(TD_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Tide::Input::GetMousePosition();
		auto width = Tide::TideApp::Get().GetWindow().GetWidth();
		auto height = Tide::TideApp::Get().GetWindow().GetHeight();
		auto bounds = m_CameraController.GetBounds();
		auto pos = m_CameraController.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_Particle.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
		{
			m_ParticleSystem.Emit(m_Particle);
		}
	}
	m_ParticleSystem.OnUpdate(ts);
	m_ParticleSystem.OnRender(m_CameraController.GetCamera());

	Tide::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Tide::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.9f }, { 1.0f, 1.0f }, m_TextureBush, 1.0f);
	Tide::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.9f }, { 1.0f, 1.0f }, m_TextureStair, 1.0f);
	Tide::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.9f }, { 1.0f, 2.0f }, m_TextureTree, 1.0f);
	Tide::Renderer2D::EndScene();
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