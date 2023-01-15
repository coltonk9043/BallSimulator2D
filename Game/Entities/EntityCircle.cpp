#include "Entity.h"
#include "../Colliders/Colliders.h"

EntityCircle::EntityCircle() : Entity() {
	float radius = rand() % 35;
	this->collider = new CircleCollider(this, radius);
	this->mass = std::_Pi * (radius * radius);
	PrepareModel();
}

EntityCircle::EntityCircle(Vector2 position) : Entity(position) {
	float radius = rand() % 35;
	this->collider = new CircleCollider(this, radius);
	this->mass = std::_Pi * (radius * radius);
	PrepareModel();
}

EntityCircle::EntityCircle(Vector2 position, float rotation) : Entity(position, rotation) {
	float radius = rand() % 35;
	this->collider = new CircleCollider(this, radius);
	this->mass = std::_Pi * (radius * radius);
	PrepareModel();
}

void EntityCircle::Update() {
    float radius = ((CircleCollider*)this->collider)->getRadius();

    if (usePhysics) {
        // Entity Update
        this->velocity = this->velocity + (this->force / this->mass);
        this->position = this->position + (this->velocity * TIMESTEP);

        if (this->position.y <= radius) {
            this->velocity.y = -this->velocity.y * this->collider->getBounciness();
            this->position.y = radius;
        }
        else {
            if (this->position.y > SCREEN_HEIGHT - radius) {
                this->velocity.y = -this->velocity.y * this->collider->getBounciness();
            }
        }
        if (this->position.x < radius) {
            this->position.x = radius;
            this->velocity.x = -this->velocity.x * this->collider->getBounciness();
        }
        else if (this->position.x > SCREEN_WIDTH - radius) {
            this->position.x = SCREEN_WIDTH - radius;
            this->velocity.x = -this->velocity.x * this->collider->getBounciness();
        }
        this->force.Set(0, GRAVITY * this->mass);
    }
}

void EntityCircle::Render(GLuint shader, double frameDelta) {
    // Finish copying position into VAO data.
    Vector2 pos = this->position + ((this->velocity * frameDelta) * TIMESTEP);
    glBindVertexArray(vao.index);

    GLint offsetLocation = glGetUniformLocation(shader, "position");
    glUniform2f(offsetLocation, pos.x, pos.y);

    glDrawElements(GL_TRIANGLES, 3 * numTriangles, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void EntityCircle::PrepareModel() {
    float radius = ((CircleCollider*)this->collider)->getRadius();

    float* vertices = new float[(numTriangles + 1) * 2];

    float* colors = new float[(numTriangles + 1) * 4];

    // set origin
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;

    colors[0] = color[0];
    colors[1] = color[1];
    colors[2] = color[2];


    unsigned int* indices = new unsigned int[numTriangles * 3];

    float pi = 4 * atanf(1.0f);
    float noTrianglesF = (float)numTriangles;
    float theta = 0.0f;

    for (unsigned int i = 0; i < numTriangles; i++) {
        // set vertices
        vertices[(i + 1) * 2 + 0] = radius * cosf(theta);
        vertices[(i + 1) * 2 + 1] = radius * sinf(theta);

        // set colors
        colors[(i + 1) * 3 + 0] = color[0];
        colors[(i + 1) * 3 + 1] = color[1];
        colors[(i + 1) * 3 + 2] = color[2];

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
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // Color VBO
    glGenBuffers(1, &vao.colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vao.colorVBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * (numTriangles + 1) * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Indices VBO
    glGenBuffers(1, &vao.indicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao.indicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * numTriangles * sizeof(float), indices, GL_STATIC_DRAW);

    // unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}