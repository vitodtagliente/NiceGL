#pragma once

#include <cstddef>

namespace nicegl
{
	class VertexBuffer
	{
	private:
		unsigned int render_id;
		std::size_t buffer_size;

	public:
		VertexBuffer(const void* data, const std::size_t _size, const unsigned int access_mode = GL_STATIC_DRAW)
			: buffer_size(_size)
		{
			glGenBuffers(1, &render_id);
			glBindBuffer(GL_ARRAY_BUFFER, render_id);
			glBufferData(GL_ARRAY_BUFFER, buffer_size, data, access_mode);
		}

		~VertexBuffer() {
			glDeleteBuffers(1, &render_id);
		}

		void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, render_id);
		}

		void unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		std::size_t size() const {
			return buffer_size;
		}
	};
}