#version 330 core

layout(location = 0) in vec2 vPosition;

out vec2 fTexCoords;

void main()
{
    gl_Position = vec4(vPosition * 2.0, 0.0, 1.0);
    fTexCoords = (vPosition + vec2(1.0)) * 0.5;
}
