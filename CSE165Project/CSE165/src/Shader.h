#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
//#include <unordered_map>

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader() {}
    ~Shader();
    // use/activate the shader
    void Bind();
    void Unbind();

    void Compile(const char* vertexSource, const char* fragmentSource);
    void SetMatrix4(const char* name, const glm::mat4& matrix);
    void checkCompileErrors(unsigned int object, std::string type);
};