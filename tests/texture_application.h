#pragma once

#include "application.h"

namespace tests
{
	class TextureApplication : public Application
	{
	public:
		IndexBuffer* ib{ nullptr };
		VertexArray* va{ nullptr };
		Program* program{ nullptr };
		Texture* texture{ nullptr };

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
			program = compile_shaders("shaders/texture_application.shader");
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

			texture->bind();
			program->set("u_Texture", 0);

			va->bind();
			ib->bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	};
}