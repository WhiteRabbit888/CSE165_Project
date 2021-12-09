#version 450 core
out vec4 color;

in vec2 texCoords;
in float texIndex;

uniform sampler2D textures[2];

void main()
{    
    int index = int(texIndex);
    color = texture(textures[index], texCoords);
}  