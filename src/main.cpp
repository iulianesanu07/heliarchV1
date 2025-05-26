#include <cstdio>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <iterator>
#include <stb/stb_image.hpp>

#include "Planet.hpp"
#include "shaderClass.hpp"
#include "EBO.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "texture.hpp"

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

  GLfloat sunVertices[] = {
    //     POSITION     //       COLOR    //  TEX COORD
    -0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // lower left corner
    -0.25f,  0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // upper left corner
     0.25f,  0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // upper right corner
     0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f    // lower left corner

  };
  
  GLfloat planetVertices[] = {
    -0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // lower left corner
    -0.25f,  0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,   // upper left corner
     0.25f,  0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // upper right corner
     0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f    // lower left corner
  };


  GLuint indices[] = {
    // sun
    0, 2, 1,
    0, 3, 2,

    // planet
    4, 6, 5,
    4, 7, 6
  };

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Test OpenGL + GLAD", nullptr, nullptr);
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

  // Sert a activer la trensparance sur les textures png
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  int windowScaler = 2;

  Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag");

  VAO VAO1;
  VAO1.Bind();

  std::vector<GLfloat> allVercices;
  allVercices.insert(allVercices.end(), std::begin(sunVertices), std::end(sunVertices));
  allVercices.insert(allVercices.end(), std::begin(planetVertices), std::end(planetVertices));

  VBO VBO1(allVercices.data(), allVercices.size() * sizeof(float));
  EBO EBO1(indices, sizeof(indices));

  VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
  VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

  VAO1.Unbind();
  VBO1.Unbind();
  EBO1.Unbind();

  Planet sun({0.0f, 0.0f, 0.0f}, 1.0f, "res/textures/planet_pack/sun.png", 1, 0.0f);
  Planet planet({0.7f, 0.0f, 0.0f}, 0.5f, "res/textures/planet_pack/iceplanet.png", 1, 0.9f);

  // Setup : lier les textures une fois
  shaderProgram.Activate();
  sun.m_texture.Bind();
  planet.m_texture.Bind();

  while (!glfwWindowShouldClose(window)) {


    glEnable(GL_SCISSOR_TEST); // active la découpe par zone

    // === Zone principale (gauche, gris)
    glViewport(0, 0, 600 * windowScaler, 600 * windowScaler);
    glScissor(0, 0, 600 * windowScaler, 600 * windowScaler); // Limite le clear à cette zone
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.Activate();

    VAO1.Bind();

    sun.draw(shaderProgram, VAO1, {0.0f, 0.0f, 0.0f}); 
    planet.draw(shaderProgram, VAO1, {0.0f, 0.0f, 0.0f}); 

    // === Panneau latéral (droite, moins gris)
    glViewport(600 * windowScaler, 0, 200 * windowScaler, 600 * windowScaler);
    glScissor(600 * windowScaler, 0, 200 * windowScaler, 600 * windowScaler);
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDisable(GL_SCISSOR_TEST); // désactivation optionnelle
    
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
      std::cerr << "OpenGL error: " << err << std::endl;
    }


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
