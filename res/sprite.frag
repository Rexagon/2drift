#version 330 core

in vec2 fTexCoords;

uniform vec4 uColor;

void main()
{
    gl_FragColor = vec4(fTexCoords, 0.0, 1.0);
}
