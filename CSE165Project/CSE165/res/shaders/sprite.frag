#version 330 core
out vec4 color;

//in vec3 inColor;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{    
    //color = vec4(inColor, 1.0);
    color = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
}  