#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
  
out vec2 texCoords;

uniform mat4 transform;

void main()
{
    texCoords = vec2(aTexCoords.x, aTexCoords.y);
    gl_Position = transform * vec4(aPos, 1.0f);
}     