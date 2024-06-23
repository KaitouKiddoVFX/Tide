#include "tdpch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Tide
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Tide::ShaderDataType::Float:	return GL_FLOAT;
			case Tide::ShaderDataType::Float2:	return GL_FLOAT;
			case Tide::ShaderDataType::Float3:	return GL_FLOAT;
			case Tide::ShaderDataType::Float4:	return GL_FLOAT;
			case Tide::ShaderDataType::Mat3:	return GL_FLOAT;
			case Tide::ShaderDataType::Mat4:	return GL_FLOAT;
			case Tide::ShaderDataType::Int:		return GL_INT;
			case Tide::ShaderDataType::Int2:	return GL_INT;
			case Tide::ShaderDataType::Int3:	return GL_INT;
			case Tide::ShaderDataType::Int4:	return GL_INT;
			case Tide::ShaderDataType::Bool:	return GL_BOOL;
		}

		TD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RenderID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RenderID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RenderID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		TD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RenderID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_FLOAT : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RenderID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}