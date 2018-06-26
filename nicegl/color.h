#pragma once

namespace nicegl
{
	struct Color
	{
		float r{ 0.0f };
		float g{ 0.0f };
		float b{ 0.0f };
		float a{ 0.0f };

		Color(){}

		Color(const float red, const float green, const float blue, const float alpha = 1.0f) {
			r = red;
			g = green;
			b = blue;
			a = alpha;
		}

		Color(const unsigned int red, const unsigned int green, 
			const unsigned int blue, const unsigned int alpha = 255) {
			r = static_cast<float>(red / 255);
			g = static_cast<float>(green / 255);
			b = static_cast<float>(blue / 255);
			a = static_cast<float>(alpha / 255);
		}
	};
}