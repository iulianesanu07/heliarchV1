#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <iterator>
#include <stb/stb_image.hpp>

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

  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  

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

  Texture sun("res/textures/SpaceAsset/Space Elements/Sun/sun1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  sun.texUnit(shaderProgram, "tex0", 0);

  Texture planet("res/textures/planet_pack/iceplanet.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
  planet.texUnit(shaderProgram, "tex0", 0);

  GLuint posUni = glGetUniformLocation(shaderProgram.ID, "pos");
  GLuint scaleUni = glGetUniformLocation(shaderProgram.ID, "scale");

  while (!glfwWindowShouldClose(window)) {

    double currentTime = glfwGetTime();
    float posx =  0.7f * sin(currentTime);
    float posy = 0.7f * cos(currentTime);

    glEnable(GL_SCISSOR_TEST); // active la découpe par zone

    // === Zone principale (gauche, gris)
    glViewport(0, 0, 600, 600);
    glScissor(0, 0, 600, 600); // Limite le clear à cette zone
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shaderProgram.Activate();

    VAO1.Bind();

    sun.Bind();
    glUniform3f(posUni, 0.0f, 0.0f, 0.0f);
    glUniform1f(scaleUni, 1.0f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    planet.Bind();
    glUniform3f(posUni, posx, posy, 0.0f);
    glUniform1f(scaleUni, 0.5f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(6 * sizeof(float)));

    // === Panneau latéral (droite, moins gris)
    glViewport(600, 0, 200, 600);
    glScissor(600, 0, 200, 600);
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
  sun.Delete();
  shaderProgram.Delete();

  glfwDestroyWindow(window);

  glfwTerminate();
  return 0;
}
