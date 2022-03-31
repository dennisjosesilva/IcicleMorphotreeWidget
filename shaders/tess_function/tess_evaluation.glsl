#version 400 core 
layout(quads, equal_spacing, ccw) in;

in vec2 positionES[];
in vec3 colorES[];

smooth out vec3 colorFS;

uniform vec3 bcolor;
uniform mat4 transform;
uniform float minValue;
uniform float maxValue;

float convParam(float u) {
  return u - 0.5;
}

float f(float u) 
{
  float x = convParam(u);
  return -(4*x*x) + 1.0f;
}

float normalisedF(float u) 
{
  return minValue + (f(u) * (maxValue - minValue));
}

vec3 rgb2hsv(vec3 rgb)
{
  float h, s, v;
  float r = rgb.r*255.f, g = rgb.g*255.f, b = rgb.b*255.f;

  float M = max(r, max(g, b));
  float m = min(r, min(g, b));
  float d = M - m;
  v = M;                         // value 
  s = (M > 0.00001) ? d / M : 0; // saturation
  if (s == 0)                    // achromatic case, hue=0 by convention
    h = 0;
  else {                         // chromatic case
    if (r == M)         h = (g - b) / d;
    else if (g == M)    h = 2.0f + (b - r) / d;
    else                h = 4.0f + (r - g) / d;
    
    h /= 6.0f;
    if (h < 0)  h += 1;
  }

  return vec3(h, s, v / 255.f);
}

vec3 hsv2rgb(vec3 hsv)
{
  float r, g, b;
  float h = hsv[0]; float s = hsv[1]; float v = hsv[2];
  
  int hueCase  = int(h * 6.0f);
  float frac   = 6 * h - hueCase;
  float lx     = v * (1.0f - s);
  float ly     = v * (1.0f - s*frac);
  float lz     = v * (1.0f - s*(1.0f - frac));
  switch (hueCase) {
    case 0:
    case 6: r = v;  g = lz; b = lx; break; // 0 < hue < 1/6
    case 1: r = ly; g = v;  b = lx; break; // 1/6 < hue < 2/6
    case 2: r = lx; g = v;  b = lz; break; // 2/6 < hue < 3/6
    case 3: r = lx; g = ly; b = v;  break; // 3/6 < hue < 4/6
    case 4: r = lz; g = lx; b = v;  break; // 4/6 < hue < 5/6
    case 5: r = v;  g = lx; b = ly; break; // 5/6 < hue < 1
  }

  return vec3(r, g, b);
}

void main()
{
  float u = gl_TessCoord.x;
  float omu = 1 - u;
  float v = gl_TessCoord.y;
  float omv = 1 - v;

  vec2 p = 
    omu * omv * positionES[0] + 
    u   * omv * positionES[1] +
    u   *   v * positionES[2] + 
    omu *   v * positionES[3];

  vec3 bcolor = 
    omu * omv * colorES[0] +
    u   * omv * colorES[1] +
    u   *   v * colorES[2] +
    omu *   v * colorES[3];

  gl_Position = transform * vec4(p, 0.0, 1.0);

  vec3 colorHSV = rgb2hsv(bcolor);
    
  // colorHSV[2] *= normalisedF(u) * normalisedF(v);
  
  
  // // set S to 1 - profile
  // colorHSV[1] = (1.0f - (normalisedF(u)) * normalisedF(v));
  
  // // set 
  // colorHSV[2] = 1.0f;

  // colorHSV[1] = 0.8f;
  // Set value 
  // colorHSV[2] *= (normalisedF(u) * normalisedF(v));
  colorHSV[1] = 1.0f - (normalisedF(u) * normalisedF(v));
  //colorHSV[2] = (normalisedF(u) * normalisedF(v));
  // colorHSV[2] = (normalisedF(u) * normalisedF(v));

  vec3 colorRGB = hsv2rgb(colorHSV);
  colorFS = colorRGB; 
}