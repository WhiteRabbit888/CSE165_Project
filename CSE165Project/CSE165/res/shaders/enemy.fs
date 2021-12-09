#version 330 core
out vec4 color;

in vec2 texCoords;

uniform sampler2D texture2;

void main()
{    
    color = texture(texture2, texCoords);
}  