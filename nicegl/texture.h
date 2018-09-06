#pragma once

#include <string>

/*
stbi_set_flip_vertically_on_load(1);
data_buffer = stbi_load(filename.c_str(), &width, &height, &num_components, 4);
*/

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

	enum class TextureState
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
		unsigned int internal_format{ GL_RGBA };
		// Format of loaded image
		unsigned int image_format{ GL_RGBA };
		// texture status
		TextureState state{ TextureState::Error };

	public:
		Texture(unsigned char * const image_data_buffer, const int image_width, const int image_height, 
			const int image_components, const TextureOptions& options = TextureOptions{}) 
		{
			// set image properties
			data_buffer = image_data_buffer;
			width = image_width;
			height = image_height;
			num_components = image_components;

			// generate the texture
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

				state = TextureState::Loaded;
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
		inline TextureState getState() const { return state; }
	};
}