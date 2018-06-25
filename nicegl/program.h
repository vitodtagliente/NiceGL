#pragma once

#include "shader.h"
#include <map>

namespace nicegl
{
	class Program
	{
	private:
		// the program id
		unsigned int id{ 0 };
		// program status
		ShaderStatus status{ ShaderStatus::Unloaded };
		// cache uniforms locations
		std::map<std::string, int> uniforms{};
		// error message
		std::string error_message{};

	public:
		Program(const std::initializer_list<Shader*> shaders) {
			id = glCreateProgram();
			status = ShaderStatus::Error;

			// attach shaders
			for (auto it = shaders.begin(); it != shaders.end(); ++it) {
				auto shader = *it;
				if (shader)
					glAttachShader(id, shader->getId());
			}

			// link the program
			glLinkProgram(id);

			int compile_status;
			glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
			if (!compile_status)
			{
				char log[1024];
				glGetShaderInfoLog(id, 1024, NULL, log);
				error_message = std::string{ log };

				glDeleteProgram(id);
			}
			else
			{
				// detach shaders
				for (auto it = shaders.begin(); it != shaders.end(); ++it) {
					auto shader = *it;
					if (shader)
						glDetachShader(id, shader->getId());
				}
				status = ShaderStatus::Compiled;
			}
		}

		~Program() {
			glDeleteProgram(id);
		}

		void bind() const {
			glUseProgram(id);
		}

		void unbind() const {
			glUseProgram(0);
		}

		inline unsigned int getId() const { return id; }
		inline ShaderStatus getStatus() const { return status; }
		inline std::string getErrorMessage() const { return error_message; }

		// set uniforms

		void set(const std::string& name, const bool value){
			glUniform1i(getUniformLocation(name), static_cast<int>(value));
		}

		void set(const std::string& name, const int value) {
			glUniform1i(getUniformLocation(name), value);
		}

		void set(const std::string& name, const float value) {
			glUniform1f(getUniformLocation(name), value);
		}

		void set(const std::string& name, const float f1, const float f2, const float f3, const float f4) {
			glUniform4f(getUniformLocation(name), f1, f2, f3, f4);
		}

	private:
		// get uniform variable location 
		inline int getUniformLocation(const std::string& name) {
			if (uniforms.find(name) != uniforms.end()) {
				return uniforms[name];
			}
			
			int location = glGetUniformLocation(id, name.c_str());
			uniforms[name] = location;
			return location;
		}
	};
}