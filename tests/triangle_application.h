#pragma once

#include "application.h"

namespace tests
{
	class TriangleApplication : public Application
	{
	public:
		VertexArray* va{ nullptr };
		Program* program{ nullptr };

		void init() override 
		{
			// position_x position_y 
			float positions[] = {
				-1.0f, -1.0f, 
				 1.0f, -1.0f, 
				 0.0f,	1.0f
			};

			// Vertex Array
			va = new VertexArray();

			VertexBuffer vb(positions, 2 * 3 * sizeof(float));
			vb.bind();

			VertexBufferLayout layout;
			layout.push<float>(3);
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
			program->set("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

			va->bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	};
}