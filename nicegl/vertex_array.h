#pragma once

#include <cstddef>
#include <assert.h>
#include <vector>
#include "vertex_buffer.h"

namespace nicegl
{
	struct VertexBufferElement
	{
		// the number of elements
		unsigned int count;
		// the type
		unsigned int type;
		unsigned char normalized;
		std::size_t size;
		
		VertexBufferElement(
			const unsigned int _count, 
			const unsigned int _type,
			const std::size_t _size,
			const unsigned char _normalized = GL_FALSE
		) 
		{
			count = _count;
			type = _type;
			normalized = _normalized;
			size = count * _size;
		}
	};

	class VertexBufferLayout
	{
	private:
		std::vector<VertexBufferElement> elements;
		std::size_t stride;

	public:
		VertexBufferLayout()
		{
			stride = 0;
		}

		template <typename T>
		void push(unsigned int count) {
			static_assert(false);
		}

		template <>
		void push<float>(unsigned int count) {
			VertexBufferElement element(count, GL_FLOAT, sizeof(float));
			elements.push_back(element);
			stride += element.size;
		}

		template <>
		void push<unsigned int>(unsigned int count) {
			VertexBufferElement element(count, GL_UNSIGNED_INT, sizeof(unsigned int));
			elements.push_back(element);
			stride += element.size;
		}

		template <>
		void push<unsigned char>(unsigned int count) {
			VertexBufferElement element(count, GL_UNSIGNED_BYTE, sizeof(unsigned int));
			elements.push_back(element);
			stride += element.size;
		}

		inline unsigned int getStride() const {	return stride; }
		inline const std::vector<VertexBufferElement> getElements() const {	return elements; }
	};

	class VertexArray
	{
	private:
		// vertex array id
		unsigned int id{ 0 };

		// bind caching 
		static unsigned int last_binded_id;

	public:
		VertexArray() {
			// generate the vertex array
			glGenVertexArrays(1, &id);
		}

		~VertexArray() {
			glDeleteVertexArrays(1, &id);
		}

		void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
			bind();
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
				offset += element.size;
			}
		}

		void bind() const {
			if (id != last_binded_id)
			{
				glBindVertexArray(id);
				last_binded_id = id;
			}
		}

		void unbind() const {
			glBindVertexArray(0);
			last_binded_id = 0;
		}

		inline unsigned int getId() const { return id; }
	};

	// vertex array cache management
	unsigned int VertexArray::last_binded_id = 0;
}