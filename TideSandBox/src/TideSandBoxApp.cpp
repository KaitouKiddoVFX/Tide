#include <Tide.h>
#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Tide::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		// m_Shader -> triangle
		m_VertexArray.reset(Tide::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Tide::Ref<Tide::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Tide::VertexBuffer::Create(vertices, sizeof(vertices)));
		Tide::BufferLayout layout = {
			{ Tide::ShaderDataType::Float3, "a_Position" },
			{ Tide::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Tide::Ref<Tide::IndexBuffer> indexBuffer;
		indexBuffer.reset(Tide::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// m_Shader -> rectangle
		m_SquareVA.reset(Tide::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Tide::Ref<Tide::VertexBuffer> squareVB;
		squareVB.reset(Tide::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Tide::ShaderDataType::Float3, "a_Position" },
			{ Tide::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Tide::Ref<Tide::IndexBuffer> squareIB;
		squareIB.reset(Tide::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// m_Shader_Source
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader = Tide::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		// m_FlatColorShader_Source
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Tide::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		// m_TextureShader
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		// m_Texture2D_object
		m_Texture = Tide::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Tide::Texture2D::Create("assets/textures/ChernoLogo.png");

		// type cast
		std::dynamic_pointer_cast<Tide::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Tide::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Tide::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Tide::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Tide::RenderCommand::Clear();
		Tide::Renderer::BeginScene(m_CameraController.GetCamera());

		// --- Array of Square ---
		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Tide::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Tide::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Tide::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Tide::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_LogoTexture->Bind();
		Tide::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		// Tide::Renderer::Submit(m_Shader, m_VertexArray);

		Tide::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Tide::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Tide::ShaderLibrary m_ShaderLibrary;
	Tide::Ref<Tide::Shader> m_Shader;
	Tide::Ref<Tide::VertexArray> m_VertexArray;

	Tide::Ref<Tide::Shader> m_FlatColorShader;
	Tide::Ref<Tide::VertexArray> m_SquareVA;

	Tide::Ref<Tide::Texture2D> m_Texture, m_LogoTexture;

	Tide::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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