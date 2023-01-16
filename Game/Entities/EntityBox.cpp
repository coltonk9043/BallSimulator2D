#include "Entity.h"

EntityBox::EntityBox() : Entity() {
    length = (rand() % 35) + 10;
    width = (rand() % 35) + 10;
    this->mass = (length * width);
    this->usePhysics = false;
    PrepareModel();
}

EntityBox::EntityBox(Vector2 position) : Entity(position) {
    float length = (rand() % 35) + 10;
    float width = (rand() % 35) + 10;
    this->mass = (length * width);
    this->usePhysics = false;
    PrepareModel();
}

EntityBox::EntityBox(Vector2 position, float rotation) : Entity(position, rotation) {
    float length = (rand() % 35) + 10;
    float width = (rand() % 35) + 10;
    this->mass = (length * width);
    this->usePhysics = false;
    PrepareModel();
}

void EntityBox::PreUpdate() {

}

void EntityBox::PostUpdate() {
    if (this->position.y <= width / 2) {
        this->velocity.y = -this->velocity.y * this->bounciness;
        this->position.y = width / 2;
    }
    else {
        if (this->position.y > SCREEN_HEIGHT - width / 2) {
            this->velocity.y = -this->velocity.y * this->bounciness;
        }
    }
    if (this->position.x < length / 2) {
        this->position.x = length / 2;
        this->velocity.x = -this->velocity.x * this->bounciness;
    }
    else if (this->position.x > SCREEN_WIDTH - length / 2) {
        this->position.x = SCREEN_WIDTH - length / 2;
        this->velocity.x = -this->velocity.x * this->bounciness;
    }
}

void EntityBox::Collision(Entity* ent) {

}

void EntityBox::Render(GLuint shader, double frameDelta) {
    // Finish copying position into VAO data.
    Vector2 pos = this->position + ((this->velocity * frameDelta) * TIMESTEP);
    glBindVertexArray(vao.index);

    GLint offsetLocation = glGetUniformLocation(shader, "position");
    glUniform2f(offsetLocation, pos.x, pos.y);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void EntityBox::PrepareModel() {
    float vertices[]{ -0.5f, -0.5f, //0 -> Bottom Left
                      -0.5f,  0.5f, //1 -> Top Left
                      0.5f, -0.5f, //2 -> Bottom Right
                      0.5f, 0.5f };//3 -> Top Right

    float colors[]{
        color[0], color[1], color[2], // top left point
        color[0], color[1], color[2], // top right point
        color[0], color[1], color[2], // bottom right point
        color[0], color[1], color[2]
    };

    GLuint indices[] = { 0, 1, 2, 1, 3, 2 };

    glGenVertexArrays(1, &vao.index);
    glBindVertexArray(vao.index);

    // Vertice VBO
    glGenBuffers(1, &vao.verticesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vao.verticesVBO);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vertices), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // Color VBO
    glGenBuffers(1, &vao.colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vao.colorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(colors), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Indices VBO
    glGenBuffers(1, &vao.indicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao.indicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}