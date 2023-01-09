#include "Entity.h"
#include "Colliders/Colliders.h"

/// <summary>
/// Entity Constructor with no parameters. Spawns at 0, 0 with a random colour.
/// </summary>
Entity::Entity() {
	this->position = Vector2(0.0f, 0.0f);
	this->rotation = 0.0f;
    this->mass = 1.0f;
    this->color[0] = (float)((rand() * 1255) % 255) / 255.0f;
    this->color[1] = (float)((rand() * 631)% 255) / 255.0f;
    this->color[2] = (float)((rand() * 12519) % 255) / 255.0f;
    PrepareModel();
    this->collider = new CircleCollider(this, radius);
}

/// <summary>
/// Entity Constructor with a position parameter.
/// </summary>
/// <param name="position">The position the ball will spawn.</param>
Entity::Entity(Vector2 position) {
	this->position = position;
	this->rotation = 0.0f;
    this->mass = 1.0f;
    this->color[0] = (float)(rand() % 255) / 255.0f;
    this->color[1] = (float)(rand() % 255) / 255.0f;
    this->color[2] = (float)(rand() % 255) / 255.0f;
    PrepareModel();
    this->collider = new CircleCollider(this, radius);
}

/// <summary>
/// Entity Constructor given a position and rotation.
/// </summary>
/// <param name="position">The position the ball will spawn.</param>
/// <param name="rotation">The rotation of the object.</param>
Entity::Entity(Vector2 position, float rotation) {
	this->position = position;
	this->rotation = rotation;
    this->mass = 1.0f;
    this->color[0] = (float)(rand() % 255) / 255.0f;
    this->color[1] = (float)(rand() % 255) / 255.0f;
    this->color[2] = (float)(rand() % 255) / 255.0f;
    PrepareModel();
}

/// <summary>
/// Entity Deconstructor
/// </summary>
Entity::~Entity() {
    glDeleteBuffers(1, &vao.verticesVBO);
    glDeleteBuffers(1, &vao.positionVBO);
    glDeleteBuffers(1, &vao.colorVBO);
    glDeleteBuffers(1, &vao.indicesEBO);
    glDeleteVertexArrays(1, &vao.index);
}

void Entity::Render(float frameDelta) {
    // Finish copying position into VAO data.
    Vector2 pos = this->position + ((this->velocity*frameDelta) * TIMESTEP);
    glBindVertexArray(vao.index);
    glBindBuffer(GL_ARRAY_BUFFER, vao.positionVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 2 * sizeof(float), pos.AsArray());
    glDrawElements(GL_TRIANGLES, 3 * numTriangles, GL_UNSIGNED_INT, 0);
}

void Entity::Update() {
    if (usePhysics) {
        // Entity Update
        this->velocity = this->velocity + (this->force / this->mass);
        this->position = this->position + (this->velocity * TIMESTEP);

        if (this->position.y <= this->radius) {
            this->velocity.y = -this->velocity.y * this->collider->getBounciness();
            this->position.y = this->radius;
        }else {
            if (this->position.y > SCREEN_HEIGHT - this->radius) {
                this->velocity.y = -this->velocity.y * this->collider->getBounciness();
            }
            this->force.Set(0, GRAVITY * this->mass);
        }
        if (this->position.x < this->radius) {
            this->position.x = this->radius;
            this->velocity.x = -this->velocity.x * this->collider->getBounciness();
        }
        else if (this->position.x > SCREEN_WIDTH - this->radius) {
            this->position.x = SCREEN_WIDTH - this->radius;
            this->velocity.x = -this->velocity.x * this->collider->getBounciness();
        }
    }
}

void Entity::CheckCollisions(std::vector<Entity*> ents) {
    for (int i = 0; i < ents.size(); i++) {
        Entity* ent = ents[i];
        if (ent == this) continue;
        CollisionInfo collision = this->collider->CheckCollision(ent);
        if (collision.collidedWith != nullptr) {
            this->OnCollide(collision);
        }
    }
}

void Entity::OnCollide(CollisionInfo info) {

}

Collider* Entity::GetCollider() {
    return this->collider;
}

void Entity::PrepareModel() {
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
        colors[(i+1) * 3 + 0] = color[0];
        colors[(i+1) * 3 + 1] = color[1];
        colors[(i+1)* 3 + 2] = color[2];
        
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
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribDivisor(1, 1);

    // Color VBO
    glGenBuffers(1, &vao.colorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vao.colorVBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * (numTriangles+1) * sizeof(float), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Indices VBO
    glGenBuffers(1, &vao.indicesEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao.indicesEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * numTriangles * sizeof(float), indices, GL_STATIC_DRAW);

    // unbind VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}