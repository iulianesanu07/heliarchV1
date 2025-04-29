#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/gl.h>
#include <stb/stb_image.hpp>

#include "shaderClass.hpp"

class Texture {
public:
  GLuint ID;
  GLenum type;
  Texture(const char *image, GLenum texType, GLenum slot,
                      GLenum format, GLenum pixelType);

  void texUnit(Shader shader, const char* uniform, GLuint unit);
  void Bind();
  void Unbind();
  void Delete();
};

#endif
