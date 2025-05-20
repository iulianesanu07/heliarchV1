#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

out vec3 color;
out vec2 texCoord;

uniform vec3 pos;
uniform float scale;

void main()
{
  vec3 scaledPos = aPos * scale;
  gl_Position = vec4((pos + scaledPos), 1.0);
  color = aColor;
  texCoord = aTex;
}
