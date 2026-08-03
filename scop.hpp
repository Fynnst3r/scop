#ifndef SCOP_HPP
#define SCOP_HPP

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GLFW/glfw3.h>

#include "includes/glm/glm.hpp"
#include "includes/glm/gtc/matrix_transform.hpp"
#include "includes/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#include "shader.hpp"

unsigned int loadTex(const char *pathToTex, unsigned int format);

#endif