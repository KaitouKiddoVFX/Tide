#pragma once

#include "Tide.h"

class ExampleLayer : public Tide::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Tide::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Tide::Event& e) override;

private:
	Tide::ShaderLibrary m_ShaderLibrary;
	Tide::Ref<Tide::Shader> m_Shader;
	Tide::Ref<Tide::VertexArray> m_VertexArray;

	Tide::Ref<Tide::Shader> m_FlatColorShader;
	Tide::Ref<Tide::VertexArray> m_SquareVA;

	Tide::Ref<Tide::Texture2D> m_Texture, m_ChernoLogoTexture;

	Tide::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};