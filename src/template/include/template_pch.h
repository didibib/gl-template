#pragma once

// STD 
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <limits.h>
#include <algorithm>
#include <random>
#include <vector>
#include <map>
#include <functional>

// OpenGL
// Include glad before glfw!
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#ifdef _WIN32
#include "GLFW/glfw3native.h"
#endif

// GLM headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/fast_square_root.hpp>

// Own headers
#include "logger.h"
#include "vertex.h"