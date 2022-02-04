#version 330 core
out vec4 fragColor;

struct Vertex
{
  vec2 pos;
  vec4 color;
};

struct Face 
{
  Vertex tl;
  Vertex tr;
  Vertex br;
  Vertex bl;
};

in Face face;

in vec2 fpos;

void main()
{
  vec2 tl = face.tl.pos;
  vec2 tr = face.tr.pos;
  vec2 bl = face.bl.pos;
  vec2 br = face.br.pos;

  float nx = (fpos.x - tl.x) / (tr.x - tl.x);
  float ny = (fpos.y - bl.y) / (tl.y - bl.y);

  vec4 tcolor = mix(face.tl.color, face.tr.color, nx);
  vec4 bcolor = mix(face.bl.color, face.br.color, nx);
  vec4 finalColor = mix(bcolor, tcolor, ny);

  fragColor = finalColor;
}