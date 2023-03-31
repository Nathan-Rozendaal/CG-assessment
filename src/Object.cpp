//
// Created by nathan on 24-03-23.
//

#include "Object.h"
#include <glm/gtc/type_ptr.hpp>
#include "objloader.h"


void Object::render(glm::mat4 view) {
  mv = view * model;

  glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));
  glBindTexture(GL_TEXTURE_2D, texture_id);
  // Send VAO
  glBindVertexArray(vao);

  //draw object
  glDrawArrays(GL_TRIANGLES, 0, mesh_vertices.size());
  glBindVertexArray(0);
}



void Object::init(GLuint program_id){
  GLuint position_id;
  GLuint normal_id;
  GLuint vbo_vertices;
  GLuint vbo_normals;
  GLuint vbo_uvs;
  glGenBuffers(1, &vbo_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
  glBufferData(GL_ARRAY_BUFFER,
                 mesh_vertices.size() * sizeof(glm::vec3), &mesh_vertices[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for normals
    glGenBuffers(1, &vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER,
                 mesh_normals.size() * sizeof(glm::vec3),
                 &mesh_normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &vbo_uvs);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
    glBufferData(GL_ARRAY_BUFFER, mesh_uvs.size() * sizeof(glm::vec2),
                 &mesh_uvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    GLuint uv_id = glGetAttribLocation(program_id, "uv");


    // Get vertex attributes
    position_id = glGetAttribLocation(program_id, "position");
    normal_id = glGetAttribLocation(program_id, "normal");
    // Allocate memory for VAO
    glGenVertexArrays(1, &vao);

    // Bind to VAO
    glBindVertexArray(vao);

    // Bind to VAO
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
    glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(uv_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind vertices to VAO
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind normals to VAO
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normal_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Stop bind to VAO
    glBindVertexArray(0);


    // Make uniform vars
    uniform_mv =glGetUniformLocation(program_id, "mv") ;
}
void Object::load_from_obj(const char *path) {
  loadOBJ(path, mesh_vertices, mesh_uvs, mesh_normals);
}
void Object::set_texture(GLuint texture_id) {
  this->texture_id = texture_id;
}
Object::Object() {
  model = glm::mat4();
}
