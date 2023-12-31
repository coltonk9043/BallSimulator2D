/*
Colton Kennedy
A class acting as a generic Entity.
1/16/2023
*/

#include "Entity.h"

/// <summary>
/// Entity Constructor with no parameters. Spawns at 0, 0 with a random colour.
/// </summary>
Entity::Entity() {
	this->position = Vector2(0.0f, 0.0f);
	this->rotation = 0.0f;
    this->mass = 1;
    this->scale.Set(1.0f, 1.0f);
    this->color[0] = (float)((rand() * 1255) % 255) / 255.0f;
    this->color[1] = (float)((rand() * 631)% 255) / 255.0f;
    this->color[2] = (float)((rand() * 12519) % 255) / 255.0f;
}

/// <summary>
/// Entity Constructor with a position parameter.
/// </summary>
/// <param name="position">The position the ball will spawn.</param>
Entity::Entity(Vector2 position, Mesh* mesh) {
	this->position = position;
    this->mesh = mesh;
	this->rotation = 0.0f;
    this->mass = 1;
    this->scale.Set(1.0f, 1.0f);
    this->color[0] = (float)(rand() % 255) / 255.0f;
    this->color[1] = (float)(rand() % 255) / 255.0f;
    this->color[2] = (float)(rand() % 255) / 255.0f;
}

/// <summary>
/// Entity Constructor given a position and rotation.
/// </summary>
/// <param name="position">The position the ball will spawn.</param>
/// <param name="rotation">The rotation of the object.</param>
Entity::Entity(Vector2 position, float rotation, Mesh* mesh) {
	this->position = position;
	this->rotation = rotation;
    this->mass = 1;
    this->scale.Set(1.0f, 1.0f);
    this->color[0] = (float)(rand() % 255) / 255.0f;
    this->color[1] = (float)(rand() % 255) / 255.0f;
    this->color[2] = (float)(rand() % 255) / 255.0f;
}

/// <summary>
/// Entity Deconstructor
/// </summary>
Entity::~Entity() {
    VAO vao = this->mesh->getVAO();
    glDeleteBuffers(1, &vao.verticesVBO);
    glDeleteBuffers(1, &vao.indicesEBO);
    glDeleteVertexArrays(1, &vao.index);
}

/// <summary>
/// Returns the bounciness factor of the Entity.
/// </summary>
/// <returns>Bounciness Factor.</returns>
float Entity::getBounciness() {
    return this->bounciness;
}

/// <summary>
/// Returns whether an entity is Kinematic.
/// </summary>
/// <returns>The kinematic state of the Entity.</returns>
bool Entity::isKinematic() {
    return this->kinematic;
}

/// <summary>
/// Sets whether the entity is kinematic.
/// </summary>
/// <param name="state">The state to set the boolean.</param>
void Entity::setKinematic(bool state) {
    this->kinematic = state;
}

/// <summary>
/// Update function. Performs Generic Entity update functions.
/// </summary>
void Entity::Update() {
    if (!kinematic) {
        // Pre-Update
        this->PreUpdate();

        // Entity Update
        this->velocity = this->velocity + (this->force / this->mass);
        this->position = this->position + (this->velocity * TIMESTEP);
        
        // Post-Update
        this->PostUpdate();

        // Gravity
        this->force.Set(0, GRAVITY * this->mass);

        if (std::fabs(this->velocity.MagnitudeSqr()) < deactivation)
        {
            this->velocity.Set(0.0f, 0.0f);
        }
    }
}

void Entity::Render(GLuint shader, double frameDelta) {
    // Finish copying position into VAO data.
    Vector2 pos = this->position + ((this->velocity * frameDelta) * TIMESTEP);
    VAO vao = mesh->getVAO();
    glBindVertexArray(vao.index);

    // Creates the model matrix and transforms it.
    Matrix4 model = Matrix4();
    model.RotateZ(this->rotation);
    model.Scale(this->scale.x, this->scale.y, 1.0f);
    model.Translate(pos.x, pos.y, 0.0f);

    GLint offsetColor = glGetUniformLocation(shader, "color");
    glUniform3f(offsetColor, this->color[0], this->color[1], this->color[2]);

    // Gets the memory location of the model matrix in shaders and writes to it.
    GLint offsetModel = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(offsetModel, 1, GL_FALSE, model.AsArray());

    // Draw the vertex array on screen.
    glDrawElements(GL_TRIANGLES, this->mesh->getIndices().size(), GL_UNSIGNED_INT, 0);

    // Unbinds the VAO
    glBindVertexArray(0);
}