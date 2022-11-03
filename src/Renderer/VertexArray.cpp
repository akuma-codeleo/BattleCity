#include "VertexArray.h"

namespace Renderer
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_id);
	}

	VertexArray::VertexArray(VertexArray&& vertexBuffer) noexcept
	{
		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& vertexBuffer) noexcept
	{
		m_id = vertexBuffer.m_id;
		vertexBuffer.m_id = 0;
		return *this;
	}

	void VertexArray::addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
	{
		bind();
		vertexBuffer.bind();
		const auto& layoutElements = layout.getLayoutElements();
		GLbyte* offset = nullptr;

		for (unsigned int i = 0; i < layoutElements.size(); ++i)
		{
			const auto& currentLayoutElement = layoutElements[i];
			GLuint currentAttribIndex = m_elementsCount + i;
			glEnableVertexAttribArray(currentAttribIndex);
			glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.normalized, layout.getStride(), offset);
			offset += currentLayoutElement.size;
		}
		m_elementsCount += static_cast<unsigned int>(layoutElements.size());
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

}