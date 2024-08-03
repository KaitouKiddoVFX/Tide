#pragma once

#include "Tide/Core/Layer.h"

#include "Tide/Events/AppEvent.h"
#include "Tide/Events/KeyEvent.h"
#include "Tide/Events/MouseEvent.h"

namespace Tide {

	class TIDE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}