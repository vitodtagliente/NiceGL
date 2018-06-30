#pragma once

#include "application.h"

namespace tests
{
	class ColorApplication : public Application
	{
	public:
		Color background_color{ 0.2f, 0.25f, 0.3f, 1.0f };

		void render() override
		{
			renderer.clear(background_color);
		}

		void gui() override
		{
			// render ImGui window
			ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Change background color:");
			ImGui::SliderFloat("r", &background_color.r, 0.0f, 1.0f);
			ImGui::SliderFloat("g", &background_color.g, 0.0f, 1.0f);
			ImGui::SliderFloat("b", &background_color.b, 0.0f, 1.0f);
		}
	};
}