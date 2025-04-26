#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderClass.hpp"
#include "EBO.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  // On force le Core Profile OpenGL 4.1 (macOS support max)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Spécifique macOS
#endif

  GLfloat vertices[] = {
      -0.5f,     -0.5f * float(sqrt(3)) / 3,    0.0f, // Lower left corner
      0.5f,      -0.5f * float(sqrt(3)) / 3,    0.0f, // Lower right corner
      0.0f,      0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
      -0.5f / 2, 0.5f * float(sqrt(3)) / 6,     0.0f, // Inner left
      0.5f / 2,  0.5f * float(sqrt(3)) / 6,     0.0f, // Inner right
      0.0f,      -0.5f * float(sqrt(3)) / 3,    0.0f  // Inner down
  };

  GLuint indices[] = {
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
  };

  GLFWwindow *window =
      glfwCreateWindow(800, 450, "Test OpenGL + GLAD", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
    return -1;
  }

  Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag");

  VAO VAO1;
  VAO1.Bind();

  VBO VBO1(vertices, sizeof(vertices));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkVBO(VBO1, 0);
  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  while (!glfwWindowShouldClose(window)) {
    glEnable(GL_SCISSOR_TEST); // active la découpe par zone

    // === Zone principale (gauche, gris)
    glViewport(0, 0, 600, 450);
    glScissor(0, 0, 600, 450); // Limite le clear à cette zone
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    shaderProgram.Activate();
    VAO1.Bind();
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

    // === Panneau latéral (droite, moins gris)
    glViewport(600, 0, 200, 450);
    glScissor(600, 0, 200, 450);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_SCISSOR_TEST); // désactivation optionnelle

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  VAO1.Delete();
  VBO1.Delete();
  EBO1.Delete();
  shaderProgram.Delete();

  glfwDestroyWindow(window);

  glfwTerminate();
  return 0;
}
