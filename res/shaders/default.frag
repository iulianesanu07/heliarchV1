#version 410 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex;

void main()
{
  FragColor = texture(tex, texCoord);
}
