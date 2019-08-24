#version 330 core

layout(location = 0) in vec2 vPosition;
layout(location = 1) in vec2 vTexCoords;

uniform vec2 uSize;
uniform mat3 uTransformationMatrix;
uniform mat3 uCameraProjectionMatrix;

out vec2 fTexCoords;

void main()
{
    gl_Position = vec4(uCameraProjectionMatrix * uTransformationMatrix * vec3(uSize * vPosition, 1.0), 1.0);
    fTexCoords = vTexCoords;
}
