#pragma once

#include <cstddef>

namespace nicegl
{
	class IndexBuffer
	{
	private:
		unsigned int render_id;
		unsigned int elements_count;
		std::size_t buffer_size;

	public:
		IndexBuffer(const unsigned int* data, const unsigned int _count, const unsigned int access_mode = GL_STATIC_DRAW)
			: elements_count(_count)
		{
			buffer_size = elements_count * sizeof(GLuint);
			glGenBuffers(1, &render_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer_size, data, access_mode);
		}

		~IndexBuffer() {
			glDeleteBuffers(1, &render_id);
		}

		void bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_id);
		}

		void unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		unsigned int count() const {
			return elements_count;
		}

		std::size_t size() const {
			return buffer_size;
		}
	};
}