#version 400 core 
layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

out vec2 positionCS;
out vec3 colorCS;

void main()
{
  positionCS = position;
  colorCS = color;
}