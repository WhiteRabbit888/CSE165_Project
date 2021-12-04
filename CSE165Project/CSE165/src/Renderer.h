#pragma once

#define GLAD_STATIC 
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
    void Draw(const VertexArray&, const IndexBuffer& ib, Shader& shader) const;
    void Clear() const;
};