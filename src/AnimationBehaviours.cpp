#include "AnimationBehaviours.h"

glm::mat4 RotationBehaviour::animationStep(float delta) {
  float rotation = currentRotation + (0.0001f * delta);
  return glm::rotate(glm::mat4(), rotation, glm::vec3(0, 1, 0));
}

glm::mat4 YMovementBehaviour::animationStep(float delta) {
  time = time + (0.0005f * delta);
  float offset = sin(time)/3000;
  return glm::translate(glm::mat4(), glm::vec3(0, offset, 0));
}

XMovementBehaviour::XMovementBehaviour(float amplitude) {
  this->amplitude = amplitude;
}
glm::mat4 XMovementBehaviour::animationStep(float delta) {
  time = time + (0.0005f * delta);
  float offset = sin(time) / 1000 * amplitude;
  return glm::translate(glm::mat4(), glm::vec3(offset, 0, 0));
}
