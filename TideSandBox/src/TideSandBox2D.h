#pragma once

#include "Tide.h"

class TideSandBox2D : public Tide::Layer
{
public:
	TideSandBox2D();
	virtual ~TideSandBox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnImGuiRender() override;

	void OnUpdate(Tide::Timestep ts) override;
	void OnEvent(Tide::Event& e) override;

private:
	Tide::OrthographicCameraController m_CameraController;

	// Temporary
	Tide::Ref<Tide::VertexArray> m_SquareVA;
	Tide::Ref<Tide::Shader> m_FlatColorShader;
	Tide::Ref<Tide::Texture2D> m_CheckerboardTexture;

	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};