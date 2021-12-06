#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <unordered_map>

class Shader
{
public:
    // the program ID
    unsigned int ID;
    std::unordered_map<std::string, int> uniformLocationCache;

    // constructor reads and builds the shader
    Shader() {}
    ~Shader();
    // use/activate the shader
    Shader &Bind();
    void Unbind();

    void Compile(const char* vertexSource, const char* fragmentSource);
    void SetInteger(const char* name, int value, bool use = false);
    void setUniform4f(const char* name, glm::vec4 val, bool use = false);
    void setUniform3f(const char* name, glm::vec3 val, bool use = false);
    void setUniform2f(const char* name, glm::vec2 val, bool use = false);
    void SetMatrix4(const char* name, const glm::mat4& matrix, bool use = false);
    void checkCompileErrors(unsigned int object, std::string type);
    //unsigned int getUniformLocation(const char* name);
};