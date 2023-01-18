#pragma once

#ifndef MESH_H
#define MESH_H

#include "Common.h"

class Mesh
{
public:
	Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
	std::vector<GLfloat> getVertices();
	std::vector<GLuint> getIndices();
	VAO getVAO();
private:
	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;
	VAO vao;
};

#endif
