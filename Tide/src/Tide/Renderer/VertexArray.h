#pragma once

#include <memory>
#include "Tide/Renderer/Buffer.h"

namespace Tide
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void AddVertexBuffer(const Tide::Ref<VertexBuffer>& VertexBuffer) = 0;
		virtual void SetIndexBuffer(const Tide::Ref<IndexBuffer>& IndexBuffer) = 0;
		virtual const std::vector<Tide::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Tide::Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		static Ref<VertexArray> Create();
	};
}