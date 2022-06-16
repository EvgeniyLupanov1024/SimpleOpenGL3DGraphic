#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Color;

void main()
{
    vec4 transform = projection * view * model * vec4(position, 1.f); 

    gl_Position = vec4(transform.xy, -transform.z, transform.w); // обратный порядок отрисовки
    Color = color;
}
