#version 400 core 
layout(vertices = 4) out;

in vec2 positionCS[];
in vec3 colorCS[];

uniform int innerSubvisionLevel;
uniform int outerSubdivisionLevel;

out vec2 positionES[];
out vec3 colorES[];

void main()
{
  positionES[gl_InvocationID] = positionCS[gl_InvocationID];
  colorES[gl_InvocationID] = colorCS[gl_InvocationID];

  gl_TessLevelInner[0] = innerSubvisionLevel;
  gl_TessLevelInner[1] = innerSubvisionLevel;
  
  gl_TessLevelOuter[0] = outerSubdivisionLevel;
  gl_TessLevelOuter[1] = outerSubdivisionLevel;
  gl_TessLevelOuter[2] = outerSubdivisionLevel;
  gl_TessLevelOuter[3] = outerSubdivisionLevel;
}