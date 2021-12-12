#version 450 core
out vec4 color;

in vec2 texCoords;

uniform sampler2D background;

void main()
{    
    color = texture(background, texCoords);
}  