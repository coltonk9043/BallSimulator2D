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

float Entity::getBounciness() {
    return this->bounciness;
}

void Entity::CheckCollisions(std::vector<Entity*> ents) {
    for (int i = 0; i < ents.size(); i++) {
        Entity* ent = ents[i];
        if (ent == this) continue;
        this->Collision(ent);
    }
}