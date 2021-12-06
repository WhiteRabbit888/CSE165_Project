#include "Shader.h"

void Shader::Compile(const char* vertexSource, const char* fragmentSource)
{
    unsigned int vertex, fragment;

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

 Shader &Shader::Bind()
{
    glUseProgram(ID);
    return *this;
}

void Shader::Unbind()
{
    glUseProgram(0);
}

void Shader::SetInteger(const char* name, int value, bool use)
{
    if (use)
        this->Bind();
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setUniform4f(const char* name, glm::vec4 val, bool use)
{
    if (use)
        this->Bind();
    glUniform4f(glGetUniformLocation(ID, name),val.x, val.y, val.z, val.w);
}

void Shader::setUniform3f(const char* name, glm::vec3 val, bool use)
{
    if (use)
        this->Bind();
    glUniform3f(glGetUniformLocation(ID, name), val.x, val.y, val.z);
}

void Shader::setUniform2f(const char* name, glm::vec2 val, bool use)
{
    if (use)
        this->Bind();
    glUniform2f(glGetUniformLocation(ID, name), val.x, val.y);
}

void Shader::SetMatrix4(const char* name, const glm::mat4& matrix, bool use)
{
    if (use)
        this->Bind();
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, false, glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
                << infoLog << "\n -- --------------------------------------------------- -- "
                << std::endl;
        }
    }
}

/*unsigned int Shader::getUniformLocation(const std::string& name)
{
    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    unsigned int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
        std::cout<< "Warning: uniform '" << name << "' doesn't exist" << std::endl;

    uniformLocationCache[name] = location;
    return location;
}*/
