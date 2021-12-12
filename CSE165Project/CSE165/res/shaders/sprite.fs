#version 450 core
out vec4 color;

in vec2 texCoords;
in float texIndex;

uniform sampler2D texture1;

void main()
{    
    color = texture(texture1, texCoords);
}  