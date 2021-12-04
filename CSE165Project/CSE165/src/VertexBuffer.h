#pragma once

class VertexBuffer
{
	unsigned int m_RendererID;	//id for specific object (vertex buffer, shader, etc.)
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};