#pragma once

#define GLAD_STATIC 
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexArray.h"
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
    //VertexArray va;
    unsigned int VAO;
    void initData();
    
public:
    Renderer(const Shader &shader);
    void Draw(const Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), glm::vec3 color = glm::vec3(1.0f));
    void Clear() const;
};

class ResourceManager
{
    // private constructor, that is we do not want any actual resource manager objects. Its members and functions should be publicly available (static).
    ResourceManager() {}
    // loads and generates a shader from file
    static Shader    loadShaderFromFile(const char* vShaderFile, const char* fShaderFile);
    // loads a single texture from file
    static Texture2D loadTextureFromFile(const char* file, bool alpha);

public:
    // resource storage
    static std::map<std::string, Shader>    Shaders;
    static std::map<std::string, Texture2D> Textures;
    // loads (and generates) a shader program from file loading vertex, fragment shader's source code
    static Shader    LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name);
    // retrieves a stored sader
    static Shader    GetShader(std::string name);
    // loads (and generates) a texture from file
    static Texture2D LoadTexture(const char* file, bool alpha, std::string name);
    // retrieves a stored texture
    static Texture2D GetTexture(std::string name);
    // properly de-allocates all loaded resources
    static void      Clear();
};