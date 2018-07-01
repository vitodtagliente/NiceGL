#pragma once

#include "vertex_array.h"
#include "index_buffer.h"

namespace nicegl
{
	class Renderable
	{
	protected:
		VertexArray* vertex_array{ nullptr };
		IndexBuffer* index_buffer{ nullptr };
		
	public:
		inline const VertexArray* getVertexArray() const { return vertex_array; }
		inline const IndexBuffer* getIndexBuffer() const { return index_buffer; }
	};
}