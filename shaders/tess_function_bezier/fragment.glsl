#version 400

smooth in vec3 colorFS;
out vec4 fragColor;

uniform float opacity;

void main()
{
  fragColor = vec4(colorFS, opacity);
}