#include "Entity.h"

Entity::Entity() {
	this->position = Vector2(0.0f, 0.0f);
	this->rotation = 0.0f;
    this->mass = 1.0f;
    PrepareModel();
}

Entity::Entity(Vector2 position) {
	this->position = position;
	this->rotation = 0.0f;
    this->mass = 1.0f;
    PrepareModel();
}

Entity::Entity(Vector2 position, float rotation) {
	this->position = position;
	this->rotation = rotation;
    this->mass = 1.0f;
    PrepareModel();
}

Entity::~Entity() {
    glDeleteBuffers(1, &vao.verticesVBO);
    glDeleteBuffers(1, &vao.positionVBO);
    glDeleteBuffers(1, &vao.indicesEBO);
    glDeleteVertexArrays(1, &vao.index);
}

void Entity::Render() {
    glBindVertexArray(vao.index);
    glDrawElementsInstanced(GL_TRIANGLES, 3 * numTriangles, GL_UNSIGNED_INT, 0, 1);
}

void Entity::Update() {
    // Entity Update
    this->velocity = this->velocity + (this->force / this->mass);
    this->position = this->position + (this->velocity / 60.0f);
    
    if (this->position.y < this->radius) this->velocity.y = -this->velocity.y;
    if (this->position.x < this->radius || this->position.x > SCREEN_WIDTH - this->radius) this->velocity.x = -this->velocity.x;

    // Resets the net force at the end.
    if (this->position.y <= this->radius) this->position.y = this->radius;
    else this->force.Set(0, GRAVITY * this->mass);

    // Finish copying position into VAO data.
    glBindBuffer(GL_ARRAY_BUFFER, vao.positionVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(float), this->position.AsArray());
}

void Entity::PrepareModel() {
    int numTriangles = 20;

    float* vertices = new float[(numTriangles + 1) * 2];

    // set origin
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;

    unsigned int* indices = new unsigned int[numTriangles * 3];

    float pi = 4 * atanf(1.0f);
    float noTrianglesF = (float)numTriangles;
    float theta = 0.0f;

    for (unsigned int i = 0; i < numTriangles; i++) {
        // set vertices
        vertices[(i + 1) * 2 + 0] = radius * cosf(theta);
        vertices[(i + 1) * 2 + 1] = radius * sinf(theta);

        // set indices
        indices[i * 3 + 0] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = i + 2;

        // step up theta
        theta += 2 * pi / numTriangles;
    }

    // set last index to wrap around to beginning
    indices[(numTriangles - 1) * 3 + 2] = 1;

    glGenVertexArrays(1, &vao.index);
    glBindVertexArray(vao.index);

    // Vertice VBO
    glGenBuffers(1, &vao.verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vao.verticesVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * (numTriangles + 1) * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vao.verticesVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // Position VBO
    glGenBuffers(1, &vao.positionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vao.positionVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float), this->position.AsArray(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vao.positionVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    // Indices VBO
    glGenBuffers(1, &vao.indicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao.indicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * numTriangles * sizeof(float), indices, GL_STATIC_DRAW);

    // unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}