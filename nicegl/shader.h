#pragma once

#include <string>
#include <fstream>
#include <map>

namespace nicegl
{
	enum class ShaderType
	{
		VertexShader,
		FragmentShader,
		GeometryShader
	};

	enum class ShaderStatus
	{
		Compiled,
		Error,
		Unloaded
	};

	class Shader
	{
	private:
		ShaderType type{ ShaderType::VertexShader };
		ShaderStatus status{ ShaderStatus::Unloaded };

		// the shader id
		unsigned int id{ 0 };

		// store compile errors into this variable
		std::string error_message{};

	public:
		Shader(const std::string& shader_source, ShaderType type = ShaderType::VertexShader)
		{
			if (type == ShaderType::VertexShader)
				id = glCreateShader(GL_VERTEX_SHADER);
			else if (type == ShaderType::FragmentShader)
				id = glCreateShader(GL_FRAGMENT_SHADER);
			else if (type == ShaderType::GeometryShader)
				id = glCreateShader(GL_GEOMETRY_SHADER);
			
			const char * source_pointer = shader_source.c_str();
			glShaderSource(id, 1, &source_pointer, NULL);
			glCompileShader(id);

			int compile_status;
			glGetShaderiv(id, GL_COMPILE_STATUS, &compile_status);
			if (!compile_status)
			{
				status = ShaderStatus::Error;
				char log[1024];
				glGetShaderInfoLog(id, 1024, NULL, log);
				error_message = std::string{ log };
			}
			else status = ShaderStatus::Compiled;
		}

		~Shader() {
			glDeleteShader(id);
			status = ShaderStatus::Unloaded;
		}

		inline unsigned int getId() const { return id; }
		inline ShaderType getType() const { return type; }
		inline ShaderStatus getStatus() const { return status; }
		inline std::string getErrorMessage() const { return error_message; }
	};

	class VertexShader : public Shader
	{
	public:
		VertexShader(const std::string& source) : Shader(source, ShaderType::VertexShader) {}
	};

	class FragmentShader : public Shader
	{
	public:
		FragmentShader(const std::string& source) : Shader(source, ShaderType::FragmentShader) {}
	};

	class GeometryShader : public Shader
	{
	public:
		GeometryShader(const std::string& source) : Shader(source, ShaderType::GeometryShader) {}
	};

	struct ShaderReader
	{
		// read a file content
		static bool load(const std::string& filename, std::string& source) {
			std::string line{};
			source.clear();
			std::ifstream file(filename);
			if (file.is_open())
			{
				while (std::getline(file, line)) {
					source += line + "\n";
				}
				file.close();
				return true;
			}
			return false;
		}

		// read different shader type sources stored into the same file
		static bool parse(const std::string& filename, std::map<ShaderType, std::string>& sources) {
			std::string line{};
			sources.clear();
			std::ifstream file(filename);
			if (file.is_open())
			{
				ShaderType current_shader_type;
				bool first_found{ false };
				std::string source{};
				while (std::getline(file, line)) {
					if (line.find("#shader") != std::string::npos)
					{
						if (first_found) {
							sources[current_shader_type] = source;
						}

						if (line.find("vertex") != std::string::npos)
							current_shader_type = ShaderType::VertexShader;
						else if (line.find("fragment") != std::string::npos)
							current_shader_type = ShaderType::FragmentShader;
						else if (line.find("geometry") != std::string::npos)
							current_shader_type = ShaderType::GeometryShader;

						source.clear();
					}

					if (first_found) {
						source += line + "\n";
					}
				}
				file.close();
				return true;
			}
			return false;
		}
	};
}