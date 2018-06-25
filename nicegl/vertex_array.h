#pragma once

#include <assert.h>
#include <vector>
#include "vertex_buffer.h"

namespace nicegl
{
	struct VertexBufferElement
	{
		unsigned int count;
		unsigned int type;
		unsigned char normalized;

		static unsigned int getSizeOfType(unsigned int type) {
			switch (type) {
			case GL_FLOAT:return 4; break;
			case GL_UNSIGNED_INT:return 4; break; 
			case GL_UNSIGNED_BYTE:return 1; break;
			}
			assert(false);
			return 0;
		}
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> elements;
		unsigned int stride;

	public:
		VertexBufferLayout()
			: stride(0)
		{

		}

		template <typename T>
		void push(unsigned int count) {
			static_assert(false);
		}

		template <>
		void push<float>(unsigned int count) {
			elements.push_back({ GL_FLOAT, count, GL_FALSE });
			stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
		}

		template <>
		void push<unsigned int>(unsigned int count) {
			elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
		}

		template <>
		void push<unsigned char>(unsigned int count) {
			elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
		}

		unsigned int getStride() const {
			return stride;
		}

		const std::vector<VertexBufferElement> getElements() const {
			return elements;
		}
	};

	class VertexArray
	{
	private:
		unsigned int render_id;

	public:
		VertexArray() {
			glGenVertexArrays(1, &render_id);
		}

		~VertexArray() {
			glDeleteVertexArrays(1, &render_id);
		}

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
			vb.bind();
			const auto& elements = layout.getElements();
			unsigned int offset = 0;
			for (unsigned int i = 0; i < elements.size(); ++i) {
				const auto& element = elements[i];
				glEnableVertexAttribArray(i);
				glVertexAttribPointer(i, element.count, element.type, 
					element.normalized,
					layout.getStride(), 
					(const void*)offset
				 );
				offset += element.count * VertexBufferElement::getSizeOfType(element.type);
			}
		}

		void bind() const {
			glBindVertexArray(render_id);
		}

		void unbind() const {
			glBindVertexArray(0);
		}
	};
}