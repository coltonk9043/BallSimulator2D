#include "Entity.h"

EntityCircle::EntityCircle() : Entity() {
    this->radius = (rand() % 35) + 10;
	this->mass = std::_Pi * (radius * radius);
    this->type = CIRCLE;
	PrepareModel();
}

EntityCircle::EntityCircle(Vector2 position) : Entity(position) {
	this->radius = (rand() % 35) + 10;
	this->mass = std::_Pi * (radius * radius);
    this->type = CIRCLE;
	PrepareModel();
}

EntityCircle::EntityCircle(Vector2 position, float rotation) : Entity(position, rotation) {
    this->radius = (rand() % 35) + 10;
	this->mass = std::_Pi * (radius * radius);
    this->type = CIRCLE;
	PrepareModel();
}

void EntityCircle::Update() {
    if (usePhysics) {
        // Entity Update
        this->velocity = this->velocity + (this->force / this->mass);
        this->position = this->position + (this->velocity * TIMESTEP);

        if (this->position.y <= radius) {
            this->velocity.y = -this->velocity.y * this->bounciness;
            this->position.y = radius;
        }
        else {
            if (this->position.y > SCREEN_HEIGHT - radius) {
                this->velocity.y = -this->velocity.y * this->bounciness;
            }
        }
        if (this->position.x < radius) {
            this->position.x = radius;
            this->velocity.x = -this->velocity.x * this->bounciness;
        }
        else if (this->position.x > SCREEN_WIDTH - radius) {
            this->position.x = SCREEN_WIDTH - radius;
            this->velocity.x = -this->velocity.x * this->bounciness;
        }
        this->force.Set(0, GRAVITY * this->mass);

        if (std::fabs(this->velocity.MagnitudeSqr()) < deactivation)
        {
            this->velocity.Set(0.0f, 0.0f);
        }
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

void EntityCircle::Collision(Entity* ent) {
    if (ent->type == CIRCLE) {
        EntityCircle* col = (EntityCircle*)ent;

        Vector2 difference = ent->position - this->position;
        float distance = difference.Magnitude();
        float distance_sqr = difference.MagnitudeSqr();
        float sum_radius = col->radius + this->radius; 
        float sum_radius_sqr = sum_radius * sum_radius;

        /*
        // Static Collision Detection
        */
        if (distance_sqr <= sum_radius_sqr) {
            Vector2 midpoint = Vector2((this->position.x + ent->position.x) / 2, (this->position.y + ent->position.y) / 2);
            this->position.Set(midpoint.x + this->radius * (this->position.x - ent->position.x) / distance, midpoint.y + col->radius * (this->position.y - ent->position.y) / distance);
            ent->position.Set(midpoint.x + col->radius * (ent->position.x - this->position.x) / distance, midpoint.y + col->radius * (ent->position.y - this->position.y) / distance);
        }

        /*
        // Dynamic Collision Detection.
        */ 

        // Gets the sum of the radius and subtracts it from the distance.
        float distance_radius = distance - sum_radius;

        // Get the velocity relative to the timestep.
        Vector2 timestepped_velocity = (this->velocity * TIMESTEP);

        // If the velocity is less than the distance between the radii of the two circles, a collision is not occuring.
        if (timestepped_velocity.Magnitude() < distance_radius) return;

        // Calculate whether the velocity is facing the object. If not, return.
        Vector2 normalized = timestepped_velocity.Normalized();
        double dot = normalized.DotProduct(difference);
        if (dot <= 0) return;

        // Get the magnitude of the difference between the entities position.
        double d = distance_sqr - (dot * dot);
        
        if (d >= sum_radius_sqr) return;


        double T = sum_radius_sqr - d;
        if (T < 0) return;


        // Therefore the distance the circle has to travel along
        // movevec is D - sqrt(T)
        double velocity_length = dot - sqrt(T);

        // Get the magnitude of the movement vector
        double mag = timestepped_velocity.Magnitude();

        // Finally, make sure that the distance A has to move
        // to touch B is not greater than the magnitude of the
        // movement vector.
        if (mag < distance_radius) {
            return;
        }

        // Dynamic collision has occured!
        Vector2 normal = difference / distance;
        Vector2 tangent = Vector2(-normal.y, normal.x);
        
        float dotTan1 = this->velocity.DotProduct(tangent);
        float dotTan2 = ent->velocity.DotProduct(tangent);

        float dotNormal1 = this->velocity.DotProduct(normal);
        float dotNormal2 = ent->velocity.DotProduct(normal);

        float totalMass = (this->mass + ent->mass);
        float m1 = this->bounciness * (dotNormal1 * (this->mass - ent->mass) + (2.0f * ent->mass * dotNormal2)) / totalMass;
        float m2 = ent->getBounciness() * (dotNormal2 * (ent->mass - this->mass) + (2.0f * this->mass * dotNormal1)) / totalMass;

        this->velocity.Set(tangent.x * dotTan1 + normal.x * m1, tangent.y * dotTan1 + normal.y * m1);
        ent->velocity.Set(tangent.x * dotTan2 + normal.x * m2, tangent.y * dotTan2 + normal.y * m2);
    }
    else if (ent->type == BOX) {

    }
}

void EntityCircle::PrepareModel() {
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