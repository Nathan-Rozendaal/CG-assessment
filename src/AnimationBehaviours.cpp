#include "AnimationBehaviours.h"

// Animation behaviour expects a mat4 transformation matrix as output
// it is recommended to use an internal variable to keep track of how much time has passed

glm::mat4 RotationBehaviour::animationStep(float delta) {
  currentRotation = currentRotation + (0.0001f * delta);
  return glm::rotate(glm::mat4(), currentRotation, glm::vec3(0, 1, 0));
}

glm::mat4 YMovementBehaviour::animationStep(float delta) {
  time = time + (0.0005f * delta);
  float offset = (sin(time)+1)/20;
  return glm::translate(glm::mat4(), glm::vec3(0, offset, 0));
}

XMovementBehaviour::XMovementBehaviour(float amplitude) {
  this->amplitude = amplitude;
}
glm::mat4 XMovementBehaviour::animationStep(float delta) {
  time = time + (0.0005f * delta);
  float offset = (cos(time) + 1) / 2 * amplitude;
  return glm::translate(glm::mat4(), glm::vec3(offset, 0, 0));
}
