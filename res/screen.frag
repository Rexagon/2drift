#version 330 core

in vec2 fTexCoords;

uniform sampler2D uScreenTexture;

void main()
{
    vec3 color = texture(uScreenTexture, fTexCoords).rgb;
    gl_FragColor = vec4(color, 1.0);
}
