#version 400 core

smooth in vec3 colorFS;
out vec4 fragColor;

void main()
{
  fragColor = vec4(colorFS, 1.0);
}