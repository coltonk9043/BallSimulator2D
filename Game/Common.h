#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <random>
#include "Matrix4.h"
#ifndef COMMON_H
#define COMMON_H

#define TICKS_PER_SECOND 60;

const float TIMESTEP = 1.0f / TICKS_PER_SECOND;
const float GRAVITY = -9.81f;
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const bool FULLSCREEN = true;

const float ANGLE_TO_RADIANS = std::_Pi / 180.0f;
const float RADIANS_TO_ANGLES = 180.0f / std::_Pi;

enum EntityType {
    CIRCLE,
    BOX,
    POLYGON
};

// Structure for VAO storing Array Object and its Buffer Objects
struct VAO {
    GLuint index;
    GLuint verticesVBO;
    GLuint colorVBO;
    GLuint indicesEBO;
};

#endif