#version 400 core
layout(quads, equal_spacing, ccw) in;

in vec2 positionES[];
in vec3 colorES[];

smooth out vec3 colorFS;

uniform mat4 transform;

void main()
{  
  float u = gl_TessCoord.x;
  float omu = 1 - u; 
  float v = gl_TessCoord.y;
  float omv = 1 - v;

  vec2 p = 
    omu * omv * positionES[0] +
    u *   omv * positionES[1] +
    u *     v * positionES[2] +
    omu *   v * positionES[3];

  gl_Position = transform * vec4(p, 0.0, 1.0);

  colorFS = 
    omu * omv * colorES[0] +
    u   * omv * colorES[1] + 
    u   *   v * colorES[2] +
    omu *   v * colorES[3];  
}