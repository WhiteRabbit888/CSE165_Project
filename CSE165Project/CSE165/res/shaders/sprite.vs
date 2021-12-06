#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 coords>
out vec2 coords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    coords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}