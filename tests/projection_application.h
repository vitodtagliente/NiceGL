#pragma once

#include "application.h"
#include "math4games.h"

using namespace m4g;

namespace tests
{
	class ProjectionApplication : public Application
	{
	public:
		IndexBuffer* ib{ nullptr };
		VertexArray* va{ nullptr };
		Program* program{ nullptr };
		Texture* texture{ nullptr };
		mat4 mvp;

		void init() override 
		{
			// position_x position_y uv_x uv_y
			float positions[] = {
				-0.5f, -0.5f, 0.0f, 0.0f,
				0.5f, -0.5f, 1.0f, 0.0f,
				0.5f,  0.5f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 1.0f
			};

			// Vertex Array
			va = new VertexArray();

			VertexBuffer vb(positions, 4 * 4 * sizeof(float));
			vb.bind();

			VertexBufferLayout layout;
			layout.push<float>(2);
			layout.push<float>(2);
			va->addBuffer(vb, layout);

			unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
			};

			ib = new IndexBuffer(indices, 6);
			ib->bind();

			va->unbind();
			vb.unbind();
			ib->unbind();

			// load texture
			unsigned char * image_data;
			int width, height, num_components;
			image_data = stbi_load("textures/batman_logo.png", &width, &height, &num_components, 4);
			texture = new Texture(image_data, width, height, num_components);
			stbi_image_free(image_data);

			// compile shaders
			program = compile_shaders("shaders/projection_application.shader");

			// projection
			mat4 projection = m4g::orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

			// view matrix (camera transform)
			mat4 view = mat4::identity;

			// model view projection matrix
			mvp = projection * view;
		}

		void uninit() override
		{
			delete va;
			delete ib;
			delete texture;
			delete program;
		}

		void render() override
		{
			program->bind();
			program->set("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);
			program->set("u_MVP", &mvp.data[0]);

			texture->bind();
			program->set("u_Texture", 0);

			va->bind();
			ib->bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	};
}