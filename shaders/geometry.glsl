#version 330 core 
layout (lines_adjacency) in;
layout (triangle_strip, max_vertices = 24) out;

in vec2 gpos[];

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

out Face face;
out vec2 fpos;

uniform vec4 centerColor;

uniform float lp;
uniform float rp;
uniform float tp;
uniform float bp;

uniform mat4 transform;

void main()
{
  vec2 tl = gpos[0];
  vec2 tr = gpos[1];
  vec2 br = gpos[2];
  vec2 bl = gpos[3];

  float width = tr.x - tl.x;
  float height = tl.y - bl.y;

  vec2 c = vec2(tl.x + (width / 2.0), bl.y + (height / 2.0));
  vec2 l = vec2(tl.x, tl.y - (height/2.0));
  vec2 t = vec2(tl.x + (width / 2.0), tl.y);
  vec2 r = vec2(tr.x, tr.y - (height / 2.0));
  vec2 b = vec2(bl.x + (width / 2.0), bl.y);

  // Quad #1
  face = Face(
    Vertex(tl, ((lp + tp) / 2.0) * centerColor),
    Vertex(t, tp * centerColor),
    Vertex(c, centerColor),
    Vertex(l, lp * centerColor));

  gl_Position = transform * vec4(tl, 0.0, 1.0);
  fpos = tl;
  EmitVertex();

  gl_Position = transform * vec4(t, 0.0, 1.0);
  fpos = t;
  EmitVertex();

  gl_Position = transform * vec4(c, 0.0, 1.0);
  fpos = c;
  EmitVertex();  
  EndPrimitive();
  
  gl_Position = transform * vec4(tl, 0.0, 1.0);
  fpos = tl;
  EmitVertex();

  gl_Position = transform * vec4(l, 0.0, 1.0);
  fpos = l;
  EmitVertex();

  gl_Position = transform * vec4(c, 0.0, 1.0);
  fpos = c;
  EmitVertex();
  EndPrimitive();

  // Quad #2
  face = Face(
    Vertex(t, tp * centerColor),
    Vertex(tr, ((tp + rp) / 2.0) * centerColor),
    Vertex(r, rp * centerColor),
    Vertex(c, centerColor));

  gl_Position = transform * vec4(t, 0.0, 1.0);
  fpos = t;
  EmitVertex();

  gl_Position = transform * vec4(c, 0.0, 1.0);
  fpos = c;
  EmitVertex();

  gl_Position = transform * vec4(r, 0.0, 1.0);
  fpos = r;
  EmitVertex();
  EndPrimitive();

  gl_Position = transform * vec4(t, 0.0, 1.0);
  fpos = t;
  EmitVertex();

  gl_Position = transform * vec4(tr, 0.0, 1.0);
  fpos = tr;
  EmitVertex();

  gl_Position = transform * vec4(r, 0.0, 1.0);
  fpos = r;
  EmitVertex();
  EndPrimitive();

  // Quad #3 
  face = Face(
    Vertex(l, lp * centerColor),
    Vertex(c, centerColor),
    Vertex(b, bp * centerColor),
    Vertex(bl, ((lp + bp) / 2.0) * centerColor));
  
  gl_Position = transform * vec4(l, 0.0, 1.0);
  fpos = l;
  EmitVertex();

  gl_Position = transform * vec4(bl, 0.0, 1.0);
  fpos = bl;
  EmitVertex();

  gl_Position = transform * vec4(b, 0.0, 1.0);
  fpos = b;
  EmitVertex();
  EndPrimitive();

  gl_Position = transform * vec4(l, 0.0, 1.0);
  fpos = l;
  EmitVertex();

  gl_Position = transform * vec4(c, 0.0, 1.0);
  fpos = c;
  EmitVertex();

  gl_Position = transform * vec4(b, 0.0, 1.0);
  fpos = b;
  EmitVertex();
  EndPrimitive();

  // Quad #4
  face = Face(
    Vertex(c, centerColor),
    Vertex(r, rp * centerColor),
    Vertex(br, ((rp + bp) / 2.0) * centerColor),
    Vertex(b, bp * centerColor));

  gl_Position = transform * vec4(c, 0.0, 1.0);
  fpos = c;
  EmitVertex();
  
  gl_Position = transform * vec4(b, 0.0, 1.0);
  fpos = b;
  EmitVertex();

  gl_Position = transform * vec4(br, 0.0, 1.0);
  fpos = br;
  EmitVertex();
  EndPrimitive();

  gl_Position = transform * vec4(c, 0.0, 1.0);
  fpos = c;
  EmitVertex();

  gl_Position = transform * vec4(r, 0.0, 1.0);
  fpos = r;
  EmitVertex();

  gl_Position = transform * vec4(br, 0.0, 1.0);
  fpos = br;
  EmitVertex();
  EndPrimitive();
}