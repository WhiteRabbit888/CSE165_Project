#version 330 core
in vec2 coords;
out vec4 color;

uniform sampler2D image;
uniform vec3 iColor;

void main()
{    
    color = vec4(iColor, 1.0) * texture(image, coords);
}  