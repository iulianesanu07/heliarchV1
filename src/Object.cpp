#include "Object.hpp"

Object::Object(glm::vec3 pos, float scale, const char* texPath, GLuint texUnit)
    : m_pos(pos), m_scale(scale), 
      m_texture(texPath, GL_TEXTURE_2D, GL_TEXTURE0 + texUnit, GL_RGBA, GL_UNSIGNED_BYTE),
      m_textureUnit(texUnit) {}

