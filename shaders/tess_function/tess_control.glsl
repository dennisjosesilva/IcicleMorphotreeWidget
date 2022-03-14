#version 400 core 
layout(vertices = 4) out;

in vec2 positionCS[];

uniform int innerSubdivisionLevel;
uniform int outerSubdivisionLevel;

out vec2 positionES[];

void main()
{
  positionES[gl_InvocationID] = positionCS[gl_InvocationID];

  gl_TessLevelInner[0] = innerSubdivisionLevel;
  gl_TessLevelInner[1] = innerSubdivisionLevel;

  gl_TessLevelOuter[0] = outerSubdivisionLevel;
  gl_TessLevelOuter[1] = outerSubdivisionLevel;
  gl_TessLevelOuter[2] = outerSubdivisionLevel;
  gl_TessLevelOuter[3] = outerSubdivisionLevel;
}