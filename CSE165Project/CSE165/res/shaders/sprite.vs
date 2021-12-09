#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in float aTexIndex;
  
out vec2 texCoords;
out float texIndex;

uniform mat4 transform;

void main()
{
    texCoords = vec2(aTexCoords.x, aTexCoords.y);
    texIndex = aTexIndex;
    gl_Position = transform * vec4(aPos, 1.0f);
}     