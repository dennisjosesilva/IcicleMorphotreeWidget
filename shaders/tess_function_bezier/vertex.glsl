#version 400 core
layout(location = 0) in vec2 position;

out vec2 positionCS;

void main()
{
  positionCS = position;
}