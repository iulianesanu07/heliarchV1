#include "Planet.hpp"
#include <GLFW/glfw3.h>

Planet::Planet(glm::vec3 pos, float scale, const char* texPath, GLuint texUnit, float orbit)
    : Object(pos, scale, texPath, texUnit),
      m_orbit(orbit){}

void Planet::draw(Shader& shader, VAO& vao, glm::vec3 pos) {
    shader.Activate();
    vao.Bind();

    m_texture.texUnit(shader, "tex", m_textureUnit);
    m_texture.Bind();

    double currentTime = glfwGetTime();
    float posx =  m_orbit * sin(currentTime);
    float posy = m_orbit * cos(currentTime);

    m_pos = {posx, posy, 0.0f};
    

    glUniform3f(glGetUniformLocation(shader.ID, "pos"), m_pos.x, m_pos.y, m_pos.z);
    glUniform1f(glGetUniformLocation(shader.ID, "scale"), m_scale);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

