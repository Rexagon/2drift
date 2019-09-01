#version 330 core

in vec2 fTexCoords;

uniform sampler2D uTexture;
uniform int uHasTexture;
uniform vec4 uColor;

void main()
{
    vec4 color = uColor;
    if (uHasTexture == 1)
    {
        color *= texture(uTexture, fTexCoords);
    }

    gl_FragColor = color;
}
