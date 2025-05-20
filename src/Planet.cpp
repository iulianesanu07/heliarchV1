#include "Planet.hpp"

Planet::Planet(glm::vec3 pos, float scale, const char* texPath, GLuint texUnit)
    : Object(pos, scale, texPath, texUnit) {}

void Planet::draw(Shader& shader, VAO& vao) {
    shader.Activate();
    vao.Bind();

    m_texture.texUnit(shader, "tex", m_textureUnit);
    m_texture.Bind();

    glUniform3f(glGetUniformLocation(shader.ID, "pos"), m_pos.x, m_pos.y, m_pos.z);
    glUniform1f(glGetUniformLocation(shader.ID, "scale"), m_scale);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

