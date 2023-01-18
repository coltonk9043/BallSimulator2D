#include "Mesh.h"

Mesh::Mesh(std::vector<GLfloat> vertices, std::vector<GLuint> indices) {
    this->vertices = vertices;
    this->indices = indices;

    // Generates the VAO and assigns the VAO index.
    glGenVertexArrays(1, &vao.index);
    glBindVertexArray(vao.index);

    //std::cout << "Vertices Size: " << vertices.size() << ", Indices Size: " << indices.size();
    
    // Vertice VBO
    glGenBuffers(1, &vao.verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vao.verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Indices VBO
    glGenBuffers(1, &vao.indicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao.indicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::vector<GLfloat> Mesh::getVertices() {
	return this->vertices;
}

std::vector<GLuint> Mesh::getIndices() {
	return this->indices;
}

VAO Mesh::getVAO() {
    return this->vao;
}