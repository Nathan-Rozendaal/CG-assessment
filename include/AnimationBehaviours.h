#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// Animation behaviour expects a mat4 transformation matrix as output
// it is recommended to use an internal variable to keep track of how much time has passed
class IAnimationBehaviour {
 public:
  virtual glm::mat4 animationStep(float delta) = 0;
};

class RotationBehaviour : public IAnimationBehaviour {
 private:
  float currentRotation = 0;
 public:
  glm::mat4 animationStep(float delta);
};

class YMovementBehaviour : public IAnimationBehaviour {
 private:
  float time = 0;
 public:
  glm::mat4 animationStep(float delta);
};

class XMovementBehaviour : public IAnimationBehaviour {
 private:
  float time = 0;
  float amplitude;
 public:
  XMovementBehaviour(float amplitude);
  glm::mat4 animationStep(float delta);
};