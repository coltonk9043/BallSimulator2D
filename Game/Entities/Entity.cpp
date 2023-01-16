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
    this->color[0] = (float)((rand() * 1255) % 255) / 255.0f;
    this->color[1] = (float)((rand() * 631)% 255) / 255.0f;
    this->color[2] = (float)((rand() * 12519) % 255) / 255.0f;
}

/// <summary>
/// Entity Constructor with a position parameter.
/// </summary>
/// <param name="position">The position the ball will spawn.</param>
Entity::Entity(Vector2 position) {
	this->position = position;
	this->rotation = 0.0f;
    this->mass = 1;
    this->color[0] = (float)(rand() % 255) / 255.0f;
    this->color[1] = (float)(rand() % 255) / 255.0f;
    this->color[2] = (float)(rand() % 255) / 255.0f;
}

/// <summary>
/// Entity Constructor given a position and rotation.
/// </summary>
/// <param name="position">The position the ball will spawn.</param>
/// <param name="rotation">The rotation of the object.</param>
Entity::Entity(Vector2 position, float rotation) {
	this->position = position;
	this->rotation = rotation;
    this->mass = 1;
    this->color[0] = (float)(rand() % 255) / 255.0f;
    this->color[1] = (float)(rand() % 255) / 255.0f;
    this->color[2] = (float)(rand() % 255) / 255.0f;
}

/// <summary>
/// Entity Deconstructor
/// </summary>
Entity::~Entity() {
    glDeleteBuffers(1, &vao.verticesVBO);
    glDeleteBuffers(1, &vao.colorVBO);
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
/// Performs collision checks on a list of Entities.
/// </summary>
/// <param name="ents">The list of Entities to be checked.</param>
void Entity::CheckCollisions(std::vector<Entity*> ents) {
    for (int i = 0; i < ents.size(); i++) {
        Entity* ent = ents[i];
        if (ent == this) continue;
        this->Collision(ent);
    }
}

/// <summary>
/// Update function. Performs Generic Entity update functions.
/// </summary>
void Entity::Update() {
    if (usePhysics) {
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