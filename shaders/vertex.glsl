#version 330 core
layout(location = 0) in vec2 aPos;

out vec2 gpos;

void main()
{
  gpos = aPos;
  // gl_Position = transform * vec4(aPos, 0.0, 1.0);
}