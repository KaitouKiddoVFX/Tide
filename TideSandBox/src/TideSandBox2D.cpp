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
	m_SquareVA = Tide::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Tide::Ref<Tide::VertexBuffer> squareVB;
	squareVB.reset(Tide::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Tide::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Tide::Ref<Tide::IndexBuffer> squareIB;
	squareIB.reset(Tide::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Tide::Shader::Create("assets/shaders/FlatColor.glsl");
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
	Tide::Renderer::BeginScene(m_CameraController.GetCamera());
	std::dynamic_pointer_cast<Tide::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Tide::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
	Tide::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	Tide::Renderer::EndScene();
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