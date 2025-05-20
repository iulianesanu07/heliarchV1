#ifndef OBJECT_CLASS_H
#define OBJECT_CLASS_H

#include <glm/glm.hpp>
#include "texture.hpp"
#include "VAO.hpp"

class Shader;

class Object {
public:
    glm::vec3 m_pos;
    float m_scale;
    Texture m_texture;
    GLuint m_textureUnit;
    GLuint m_posUni;
    GLuint m_scaleUni;

    Object(glm::vec3 pos, float scale, const char* texPath, GLuint texUnit);

    virtual void draw(Shader& shader, VAO& vao) = 0;
    virtual ~Object() {}
};

#endif

