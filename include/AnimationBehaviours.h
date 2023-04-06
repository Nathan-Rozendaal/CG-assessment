#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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