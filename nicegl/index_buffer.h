#pragma once

#include <cstddef>

namespace nicegl
{
	class IndexBuffer
	{
	private:
		// buffer id
		unsigned int id{ 0 };
		// the size of the buffer
		std::size_t buffer_size{ 0 };
		// num of elements
		unsigned int elements_count{ 0 };

	public:
		IndexBuffer(const unsigned int* data, const unsigned int count, const unsigned int access_mode = GL_STATIC_DRAW) {
			elements_count = count;
			buffer_size = elements_count * sizeof(GLuint);
			// gnerate the buffer
			glGenBuffers(1, &id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			// fill the buffer
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, data, access_mode);
		}

		~IndexBuffer() {
			glDeleteBuffers(1, &id);
		}

		void bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		}

		void unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		inline unsigned int getId() const { return id; }
		inline std::size_t size() const { return buffer_size; }
		inline unsigned int count() const { return elements_count; }
	};
}