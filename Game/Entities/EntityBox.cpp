#include "Entity.h"

EntityBox::EntityBox() : Entity() {
    length = (rand() % 50) + 200;
    width = (rand() % 10) + 20;
    rotation = (rand() % 360);
    scale.Set(length, width);
    this->mass = (length * width);
    this->type = BOX;
    this->kinematic = true;
}

EntityBox::EntityBox(Vector2 position, Mesh* mesh) : Entity(position, mesh) {
    length = (rand() % 50) + 200;
    width = (rand() % 10) + 20;
    rotation = (rand() % 360);
    scale.Set(length, width);
    this->mass = (length * width);
    this->type = BOX;
    this->kinematic = true;
}

EntityBox::EntityBox(Vector2 position, float rotation, Mesh* mesh) : Entity(position, rotation, mesh) {
    length = (rand() % 50) + 200;
    width = (rand() % 10) + 20;
    rotation = (rand() % 360);
    scale.Set(length, width);
    this->mass = (length * width);
    this->type = BOX;
    this->kinematic = true;
}

void EntityBox::PreUpdate() {

}

void EntityBox::PostUpdate() {
    if (this->position.y <= width / 2) {
        this->velocity.y = -this->velocity.y * this->bounciness;
        this->position.y = width / 2;
    }
    else if (this->position.y > SCREEN_HEIGHT - width / 2) {
        this->velocity.y = -this->velocity.y * this->bounciness;
        this->position.y = SCREEN_HEIGHT - width / 2;
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

void EntityBox::CheckCollisions(std::vector<Entity*> ents) {

}

float EntityBox::getWidth() {
    return this->width;
}

float EntityBox::getLength() {
    return this->length;
}