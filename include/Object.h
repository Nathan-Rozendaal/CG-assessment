//
// Created by nathan on 24-03-23.
//


#ifndef SIMPLE_OPENGL_OBJECT_H
#define SIMPLE_OPENGL_OBJECT_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

using namespace std;

class Object {
 private:
  vector<glm::vec3> mesh_normals;
  vector<glm::vec3> mesh_vertices;
  vector<glm::vec2> mesh_uvs;
  glm::mat4 mv;
  glm::mat4 model;

  GLuint uniform_mv;
  GLuint vao;
  GLuint texture_id;



 public:
  Object();
  void render(glm::mat4 view);
  void init(GLuint program_id);
  void load_from_obj(const char * path);
  void set_texture(GLuint texture_id);

};

#endif  // SIMPLE_OPENGL_OBJECT_H
