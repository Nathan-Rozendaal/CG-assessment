#ifndef SIMPLE_OPENGL_GLSL_HPP
#define SIMPLE_OPENGL_GLSL_HPP

#include <GL/glew.h>

class glsl {
 private:
  static char* contents;
  static GLuint makeShader(const char* source, int type);

 public:
  glsl() = default;
  ~glsl() = default;
  static char* readFile(const char* filename);
  static bool compiledStatus(GLint id);
  static GLuint makeVertexShader(const char* source);
  static GLuint makeFragmentShader(const char* source);
  static GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID);
};

#endif  // SIMPLE_OPENGL_GLSL_HPP
