#ifndef PLANET_CLASS_H
#define PLANET_CLASS_H

#include "Object.hpp"
#include "shaderClass.hpp"

class Planet : public Object {
public:
    float m_orbit;
    
    Planet(glm::vec3 pos, float scale, const char* texPath, GLuint texUnit, float orbit);
    void draw(Shader& shader, VAO& vao, glm::vec3 pos) override;
};

#endif

