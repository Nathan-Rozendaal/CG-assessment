#include <iostream>


#include <GL/glew.h>
#include <GL/freeglut.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.hpp"
#include "IBL.h"
#include "Model.h"
#include "shader.h"
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION
using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 1920, HEIGHT = 1080;
int window=0;

const char* fragshader_name = "shaders/fragpbr.frag";
const char* vertexshader_name = "shaders/vertprb.vert";

unsigned const int DELTA_TIME =10;

vector<Model> models = vector<Model>();
vector<Shader> shaders = vector<Shader>();

Maps maps;

Camera camera1(glm::vec3(0.0f, 1.75f, 4.0f));
Camera camera2(glm::vec3(6.0f, 4.5f, 6.0f), false, glm::vec3(0.0f, 1.0f, 0.0f), -125, -30);

Camera* activecam = &camera1;


float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

glm::vec3 lightPositions[] = {
    glm::vec3(-4.0f, 4.5f, 5.5f),
    glm::vec3( 4.0f, 4.5f, 5.5f),
    glm::vec3(-4.0f, 4.5f, -5.5f),
    glm::vec3(4.0f, 4.5f, -5.5f), 
    glm::vec3(-4.0f, 4.5f, 0.0f), 
    glm::vec3(4.0f, 4.5f, 0.0f)
};
glm::vec3 lightColors[] = {
    glm::vec3(70.0f, 70.0f, 70.0f),
    glm::vec3(70.0f, 70.0f, 70.0f),
    glm::vec3(70.0f, 70.0f, 70.0f),
    glm::vec3(70.0f, 70.0f, 70.0f),
    glm::vec3(70.0f, 70.0f, 70.0f),
    glm::vec3(70.0f, 70.0f, 70.0f)
};


//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------
// ID's
GLuint program_id;

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
  if (key == 27)
    glutExit();
  if (key == 'w')
    activecam->ProcessKeyboard(FORWARD, DELTA_TIME);
  if (key == 's')
    activecam->ProcessKeyboard(BACKWARD, DELTA_TIME);
  if (key == 'a')
    activecam->ProcessKeyboard(LEFT, DELTA_TIME);
  if (key == 'd')
    activecam->ProcessKeyboard(RIGHT, DELTA_TIME);
  if (key == 'v')
    if (activecam == &camera1) {
      activecam = &camera2;
    } else {
      activecam = &camera1;
    }
    
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
  // Define background
  glClearColor(0.0, 0.0, 0.4, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shaders[0].use();

  for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i) {
    shaders[0].setVec3("lightPositions[" + std::to_string(i) + "]", lightPositions[i]);
    shaders[0].setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
  }
  shaders[0].setFloat("ao", 1.0f);

  glViewport(0, 0, WIDTH, HEIGHT);



  glm::mat4 projection = glm::perspective(glm::radians(activecam->Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
  glm::mat4 view = activecam->GetViewMatrix();

  models[0].model = glm::rotate(models[0].model, 0.0001f * DELTA_TIME, glm::vec3(0, 1, 0));
  models[1].model = glm::rotate(models[1].model, 0.0001f * DELTA_TIME, glm::vec3(0, 1, 0));

  shaders[0].setMat4("projection", projection);
  shaders[0].setMat4("view", view);
  shaders[0].setVec3("camPos", activecam->Position);

  // bind pre-computed IBL data
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, maps.irradianceMap);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_CUBE_MAP, maps.prefilterMap);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, maps.brdfLUTTexture);


  for (auto & model : models) {
    model.Draw(shaders[0]);
  }

  // Swap buffers
  glutSwapBuffers();
}


//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
  Render();
  glutTimerFunc(DELTA_TIME, Render, 0);
}
void mouse_callback(int x, int y)
{
  float xpos = static_cast<float>(x);
  float ypos = static_cast<float>(y);

  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  activecam->ProcessMouseMovement(xoffset, yoffset);

  if ( (x > 300 && x < WIDTH - 300) && (y > 300 && y < HEIGHT - 300))
    return;

  lastX = WIDTH/2;   //centers the last known position, this way there isn't an odd jump with your cam as it resets
  lastY = HEIGHT/2;
  glutWarpPointer(WIDTH/2, HEIGHT/2);  //centers the cursor

}
void mouseWheel(int button, int dir, int x, int y) {
  activecam->ProcessMouseScroll(dir);
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char** argv)
{
  glutInit(&argc, argv);

  glutSetOption(GLUT_MULTISAMPLE, 8);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

  glutInitWindowSize(WIDTH, HEIGHT);
  window = glutCreateWindow("Hello OpenGL");

  glutDisplayFunc(Render);
  glutKeyboardFunc(keyboardHandler);
  glutTimerFunc(DELTA_TIME, Render, 0);
  glutPassiveMotionFunc(mouse_callback);
  glutMouseWheelFunc(mouseWheel);
  glutSetCursor(GLUT_CURSOR_NONE);

  glEnable(GL_DEPTH_TEST);
  // set depth function to less than AND equal for skybox depth trick.
  glDepthFunc(GL_LEQUAL);
  // enable seamless cubemap sampling for lower mip levels in the pre-filter map.
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);

  glewInit();
}


//------------------------------------------------------------
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------

void InitShaders()
{
  shaders.push_back(Shader(vertexshader_name, fragshader_name));
  program_id = shaders[0].ID;
  // set texture indices
  shaders[0].use();
  shaders[0].setInt("irradianceMap", 0);
  shaders[0].setInt("prefilterMap", 1);
  shaders[0].setInt("brdfLUT", 2);

  // bind samplers to a dummy texture first
  shaders[0].setInt("texture_diffuse1", 1);
  shaders[0].setInt("texture_normal1", 1);
  shaders[0].setInt("texture_roughness1", 1);
  shaders[0].setInt("texture_metallic1", 1);
}
void LoadModels() 
{
  models.push_back(Model("OBJs/platform/platform.gltf"));

  models.push_back(Model("OBJs/lotus/lotus.gltf"));
  models[1].model = glm::translate(glm::mat4(), glm::vec3(0, 0.08, 0));

  models.push_back(Model("OBJs/ferrari_312t/ferrari_312t.gltf"));
  models[2].model = glm::translate(glm::rotate(glm::mat4(), -1.0f, glm::vec3(0, 1, 0)), glm::vec3(-5, 0, 0));

  models.push_back(Model("OBJs/lotus49/lotus49.gltf"));
  models[3].model = glm::translate(glm::rotate(glm::mat4(), 1.0f, glm::vec3(0, 1, 0)), glm::vec3(5, 0, 0));

  models.push_back(Model("OBJs/lotus98t/lotus98t.gltf"));
  models[4].model = glm::translate(glm::mat4(), glm::vec3(5, 0, 0));

  models.push_back(Model("OBJs/ferrari_312/ferrari_312.gltf"));
  models[5].model = glm::translate(glm::mat4(), glm::vec3(-5, 0, 0));
  models.push_back(Model("OBJs/Room/Room.gltf"));
}

int main(int argc, char** argv)
{
  InitGlutGlew(argc, argv);

  InitShaders();

  LoadModels();

  maps = initIBL();

  // Main loop
  glutMainLoop();

  return 0;
}