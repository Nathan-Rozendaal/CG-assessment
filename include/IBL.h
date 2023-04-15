//
// Created by nathan on 29-03-23.
//

#ifndef SIMPLE_OPENGL_IBL_H
#define SIMPLE_OPENGL_IBL_H

#endif  // SIMPLE_OPENGL_IBL_H
#include "glsl.hpp"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include "shader.h"
#include "iostream"
#include "vector"
#define STB_IMAGE_IMPLEMENTATION

struct Maps{
  unsigned int irradianceMap;
  unsigned int prefilterMap;
  unsigned int brdfLUTTexture;
};

// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
void renderCube();

// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
void renderQuad();

Maps initIBL(const char* hdrPath);