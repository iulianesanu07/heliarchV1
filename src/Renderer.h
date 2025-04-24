#pragma once

#include <GL/glew.h>

// Macros servant a ne pas "polluer" le code
#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    __builtin_debugtrap();
#define GLCall(x)                                                              \
  GLClearError();                                                              \
  x;                                                                           \
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))

// Nettoie la pile d'erreurs pour la garder "propre" et n'avoir que l'essentiel
void GLClearError();

// Bloque le programme et affiche l'erreur, la ligne et la fonction ayant
// provoque le bordel si glGetError() contient quelque chose AKA si une erreur a
// eu lieu
bool GLLogCall(const char *function, const char *file, int line);
