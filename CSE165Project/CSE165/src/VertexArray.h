#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
	unsigned int m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};