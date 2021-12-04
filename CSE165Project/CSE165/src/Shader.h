#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Shader
{
    // the program ID
    unsigned int ID;
    std::unordered_map<std::string, int> uniformLocationCache;

public:
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    // use/activate the shader
    void Bind();
    void Unbind();

    void setUniform4f(const std::string& name, float v0, float v1, float f1, float f2);
    unsigned int getUniformLocation(const std::string& name);
};