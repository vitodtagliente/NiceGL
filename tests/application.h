#pragma once

#include "nicegl/nicegl.h"

using namespace nicegl;

namespace tests
{
	class Application
	{
	protected:
		Renderer renderer;

	public:
		Application(){}
		virtual ~Application(){}

		virtual void init(){}
		virtual void update(const float delta_time = 0.0f){}
		virtual void render(){}
		virtual void gui(){}
		virtual void uninit(){}

		Program* compile_shaders(const std::string& shader_filename) {
			// parse the shader source
			std::map<ShaderType, std::string> sources;
			ShaderReader::parse(shader_filename, sources);

			// compile vertex shader
			VertexShader vs(sources[ShaderType::VertexShader]);
			if (vs.getStatus() == ShaderStatus::Error) {
				std::cout << vs.getErrorMessage() << std::endl;
			}
			else
			{
				std::cout << "Vertex Shader" << std::endl << std::endl;
				std::cout << sources[ShaderType::VertexShader] << std::endl << std::endl;
			}

			// compile fragment shader
			FragmentShader fs(sources[ShaderType::FragmentShader]);
			if (fs.getStatus() == ShaderStatus::Error) {
				std::cout << fs.getErrorMessage() << std::endl;
			}
			else
			{
				std::cout << "Fragment Shader" << std::endl << std::endl;
				std::cout << sources[ShaderType::FragmentShader] << std::endl << std::endl;
			}

			// compile the shader program
			Program* program = new Program({ &vs, &fs });
			if (program->getStatus() == ShaderStatus::Error) {
				std::cout << program->getErrorMessage() << std::endl;
			}

			program->unbind();
			return program;
		}
	};
}