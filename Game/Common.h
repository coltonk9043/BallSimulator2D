#pragma once

#ifndef COMMON_H
#define COMMON_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <al.h>
#include <alc.h>
#include <vector>
#include <random>
#include <iostream>
#include "Matrix4.h"
#include <string>

#define TICKS_PER_SECOND 60;

const float TIMESTEP = 1.0f / TICKS_PER_SECOND;
const float GRAVITY = -9.81f;
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const bool FULLSCREEN = true;

const double PI = 3.14159265358979311599796346854;

// Model Variables
const unsigned int TRIANGLE_RESOLUTION = 20;

const float ANGLE_TO_RADIANS = PI / 180.0f;
const float RADIANS_TO_ANGLES = 180.0f / PI;

enum EntityType {
    CIRCLE,
    BOX,
    POLYGON
};

// Structure for VAO storing Array Object and its Buffer Objects
struct VAO {
    GLuint index;
    GLuint verticesVBO;
    GLuint indicesEBO;
};

#endif