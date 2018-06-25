#pragma once

#include <string>
#include "stb_image.h"

namespace nicegl
{
	struct TextureOptions
	{
		// Wrapping mode on S axis
		unsigned int wrapS{ GL_REPEAT };
		// Wrapping mode on T axis
		unsigned int wrapT{ GL_REPEAT };
		// Filtering mode if texture pixels < screen pixels
		unsigned int filterMin{ GL_LINEAR };
		// Filtering mode if texture pixels > screen pixels
		unsigned int filterMax{ GL_LINEAR };
	};

	enum class TextureStatus
	{
		Loaded,
		Error
	};

	class Texture
	{
	private:
		// texture id
		unsigned int id{ 0 };
		// texture dimensions
		int width{ 0 }, height{ 0 };
		// local image data buffer 
		unsigned char * data_buffer{};
		// num of components: bitperpixel
		int num_components{ 0 };
		// Format of texture object
		unsigned int internal_format;
		// Format of loaded image
		unsigned int image_format;
		// texture status
		TextureStatus status{ TextureStatus::Error };

	public:
		Texture(const std::string& filename, const TextureOptions& options = TextureOptions{}) {
			stbi_set_flip_vertically_on_load(1);
			data_buffer = stbi_load(filename.c_str(), &width, &height, &num_components, 4);

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			/* set the texture wrapping/filtering options (on the currently bound texture object) */
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, options.wrapS);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, options.wrapT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, options.filterMin);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, options.filterMax);

			if (data_buffer) {
				if (num_components == 1)
					this->image_format = GL_RED;
				else if (num_components == 3)
					this->image_format = GL_RGB;
				else if (num_components == 4)
					this->image_format = GL_RGBA;
				this->internal_format = this->image_format;

				glTexImage2D(GL_TEXTURE_2D, 0, internal_format,	width, height, 
					0, image_format, GL_UNSIGNED_BYTE, data_buffer
				);

				status = TextureStatus::Loaded;
			}			
		}

		~Texture() {
			glDeleteTextures(1, &id);
		}

		void bind(unsigned int slot = 0) const {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		inline unsigned int getId() const { return id; }
		inline int getWidth() const { return width;	}
		inline int getHeight() const { return height; }
		inline TextureStatus getStatus() const { return status; }
	};
}