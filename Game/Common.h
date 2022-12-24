#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef COMMON_H
#define COMMON_H

const float GRAVITY = -9.81f;
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
// structure for VAO storing Array Object and its Buffer Objects
struct VAO {
    GLuint index;
    GLuint verticesVBO;
    GLuint positionVBO;
    GLuint indicesEBO;
};

#endif