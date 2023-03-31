#include "glsl.hpp"

#include <fstream>
#include <memory>

char* glsl::readFile(const char* filename) {
  std::ifstream stream(filename);

  stream.seekg(0, std::ifstream::end);
  long size = stream.tellg();
  stream.seekg(0, std::ifstream::beg);

  char* content = new char[size + 1];

  // zero out memory
  for (int i = 0; i < size + 1; i++) {
    content[i] = 0;
  }

  stream.read(content, size);

  stream.close();

  content[size + 1] = '\0';

  return content;
}

bool glsl::compiledStatus(GLint id) {
  GLint compiled;
  glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

  if (compiled) {
    return true;
  } else {
    GLint logLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);

    std::unique_ptr<char> log(new char[logLength]);
    glGetShaderInfoLog(id, logLength, nullptr, log.get());

    printf("%s\n", log.get());

    return false;
  }
}

GLuint glsl::makeVertexShader(const char* source) {
  return makeShader(source, GL_VERTEX_SHADER);
}

GLuint glsl::makeFragmentShader(const char* source) {
  return makeShader(source, GL_FRAGMENT_SHADER);
}

GLuint glsl::makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID) {
  auto program = glCreateProgram();

  glAttachShader(program, vertexShaderID);
  glAttachShader(program, fragmentShaderID);
  glLinkProgram(program);

  return program;
}

GLuint glsl::makeShader(const char* source, int type) {
  auto id = glCreateShader(type);

  glShaderSource(id, 1, (const GLchar**)&source, nullptr);
  glCompileShader(id);

  bool compiledCorrectly = compiledStatus(id);
  if (compiledCorrectly) {
    return id;
  }
  return -1;
}
