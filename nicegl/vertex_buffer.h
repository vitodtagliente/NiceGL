#pragma once

#include <cstddef>

namespace nicegl
{
	class VertexBuffer
	{
	private:
		// buffer id
		unsigned int id{ 0 };
		// the size of the buffer
		std::size_t buffer_size{ 0 };

	public:
		VertexBuffer(const void* data, const std::size_t _size, const unsigned int access_mode = GL_STATIC_DRAW)
			: buffer_size(_size)
		{
			// generate the buffer
			glGenBuffers(1, &id);
			glBindBuffer(GL_ARRAY_BUFFER, id);
			// fill the buffer with data
			glBufferData(GL_ARRAY_BUFFER, buffer_size, data, access_mode);
		}

		~VertexBuffer() {
			glDeleteBuffers(1, &id);
		}

		void bind() const {
			glBindBuffer(GL_ARRAY_BUFFER, id);
		}

		void unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		inline unsigned int getId() const { return id; }
		inline std::size_t size() const { return buffer_size; }
	};
}