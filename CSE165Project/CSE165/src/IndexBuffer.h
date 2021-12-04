#pragma once

class IndexBuffer
{
	unsigned int m_RendererID;	//id for specific object (vertex buffer, shader, etc.)
	unsigned int m_Count;
public:
	IndexBuffer(const void* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};