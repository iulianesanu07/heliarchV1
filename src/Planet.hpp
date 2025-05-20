#ifndef PLANET_CLASS_H
#define PLANET_CLASS_H

#include "Object.hpp"
#include "shaderClass.hpp"

class Planet : public Object {
public:
    Planet(glm::vec3 pos, float scale, const char* texPath, GLuint texUnit);
    void draw(Shader& shader, VAO& vao) override;
};

#endif

