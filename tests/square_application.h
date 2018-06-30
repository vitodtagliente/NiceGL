#pragma once

#include "application.h"

namespace tests
{
	class SquareApplication : public Application
	{
	public:
		VertexArray* va{ nullptr };
		Program* program{ nullptr };
		Color square_color{ 1.0f, 0.0f, 0.0f};

		void init() override 
		{
			// position_x position_y 
			float positions[] = {
				-0.5f, -0.5f,
				 0.5f, -0.5f,
				-0.5f,  0.5f,
				 0.5f,  0.5f,
				 0.5f, -0.5f,
				-0.5f,  0.5f
			};

			// Vertex Array
			va = new VertexArray();

			VertexBuffer vb(positions, 2 * 6 * sizeof(float));
			vb.bind();

			VertexBufferLayout layout;
			layout.push<float>(2);
			va->addBuffer(vb, layout);
			
			va->unbind();
			vb.unbind();
			
			// compile shaders
			program = compile_shaders("shaders/triangle_application.shader");
		}

		void uninit() override
		{
			delete va;
			delete program;
		}

		void render() override
		{
			program->bind();
			program->set("u_Color", square_color.r, square_color.g, square_color.b, square_color.a);

			va->bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	};
}