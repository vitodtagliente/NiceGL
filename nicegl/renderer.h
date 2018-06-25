#pragma once

#include "color.h"

namespace nicegl
{
	class Renderer
	{
	private:

	public:

		void clear() {
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void clear(Color& color) {
			clear();
			// clear background color
			glClearColor(color.r, color.g, color.b, color.a);
		}
	};
}