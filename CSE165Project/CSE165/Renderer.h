#pragma once

#define GLAD_STATIC 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"

#include <map>
#include <string>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
    Shader shader;
    unsigned int VAO;
    void initData();
    
public:
    Renderer(const Shader &shader);
    void Draw(const Texture2D &textname, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color);
};