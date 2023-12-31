#include "Entity.h"

/// <summary>
/// Blank Circle Entity Constructor
/// </summary>
EntityCircle::EntityCircle() : Entity() {
    this->radius = (rand() % 35) + 10;
    scale.Set(radius, radius);
	this->mass = PI * (radius * radius);
    this->type = CIRCLE;
}

/// <summary>
/// Circle Entity Constructor given position.
/// </summary>
/// <param name="position">The position the Entity will spawn.</param>
EntityCircle::EntityCircle(Vector2 position, Mesh* mesh) : Entity(position, mesh) {
	this->radius = (rand() % 35) + 10;
    scale.Set(radius, radius);
	this->mass = PI * (radius * radius);
    this->type = CIRCLE;
}

/// <summary>
/// Circle Entity constructor given position and rotation.
/// </summary>
/// <param name="position">The position that the entity will spawn.</param>
/// <param name="rotation">The rotation that the entity will spawn with.</param>
EntityCircle::EntityCircle(Vector2 position, float rotation, Mesh* mesh) : Entity(position, rotation, mesh) {
    this->radius = (rand() % 35) + 10;
    scale.Set(radius, radius);
	this->mass = PI * (radius * radius);
    this->type = CIRCLE;
}


void EntityCircle::PreUpdate() {

}

void EntityCircle::PostUpdate() {
    if (this->position.y <= radius) {
        this->velocity.y = -this->velocity.y * this->bounciness;
        this->position.y = radius;
    }
    else if (this->position.y > SCREEN_HEIGHT - radius) {
        this->velocity.y = -this->velocity.y * this->bounciness;
        this->position.y = SCREEN_HEIGHT - radius;
    }
    if (this->position.x < radius) {
        this->position.x = radius;
        this->velocity.x = -this->velocity.x * this->bounciness;
    }
    else if (this->position.x > SCREEN_WIDTH - radius) {
        this->position.x = SCREEN_WIDTH - radius;
        this->velocity.x = -this->velocity.x * this->bounciness;
    }
}

void EntityCircle::CheckCollisions(std::vector<Entity*> ents) {
    if (this->kinematic) return;

    for (int i = 0; i < ents.size(); i++) {
        Entity* ent = ents[i];
        if (ent == this) continue;
        
        if (ent->type == CIRCLE) {
            EntityCircle* col = (EntityCircle*)ent;

            Vector2 difference = ent->position - this->position;
            float distance = difference.Magnitude();
            float distance_sqr = difference.MagnitudeSqr();
            float sum_radius = col->radius + this->radius;
            float sum_radius_sqr = sum_radius * sum_radius;

            /*
            // Static Collision Detection
            // TODO: This needs to be fixed to set the position and set velocity to ZERO OR Tangent.
            */
            if (distance_sqr < sum_radius_sqr) {
                Vector2 midpoint = Vector2((this->position.x + ent->position.x) * 0.5f, (this->position.y + ent->position.y) * 0.5f);

                this->position.Set(midpoint.x + this->radius * (this->position.x - ent->position.x) / distance, midpoint.y + this->radius * (this->position.y - ent->position.y) / distance);
                this->velocity.Set(0, 0);
                //if(!ent->isKinematic())
                //    ent->position.Set(midpoint.x + col->radius * (ent->position.x - this->position.x) / distance, midpoint.y + col->radius * (ent->position.y - this->position.y) / distance);
            }

            /*
            // Dynamic Collision Detection.
            */
            // Gets the sum of the radius and subtracts it from the distance.
            float distance_radius = distance - sum_radius;

            // Get the velocity relative to the timestep.
            Vector2 timestepped_velocity = (this->velocity * TIMESTEP);

            // If the velocity is less than the distance between the radii of the two circles, a collision is not occuring.
            if (timestepped_velocity.Magnitude() < distance_radius) continue;

            // Calculate whether the velocity is facing the object. If not, return.
            Vector2 normalized = timestepped_velocity.Normalized();
            double dot = normalized.DotProduct(difference);
            if (dot <= 0) continue;

            // Get the magnitude of the difference between the entities position.
            double d = distance_sqr - (dot * dot);
            if (d >= sum_radius_sqr) continue;

            // Get the 
            double T = sum_radius_sqr - d;
            if (T < 0) continue;

            // Therefore the distance the circle has to travel along
            // movevec is D - sqrt(T)
            double velocity_length = dot - sqrt(T);

            // Get the magnitude of the movement vector
            double mag = timestepped_velocity.Magnitude();

            // Ensure that the distance required is not bigger than the magnitude of the velocity vector.
            if (mag < distance_radius) continue;

            // Dynamic collision has occured!
            Vector2 normal = difference / distance;
            Vector2 tangent = Vector2(-normal.y, normal.x);

            float dotTan1 = this->velocity.DotProduct(tangent);
            float dotTan2 = ent->velocity.DotProduct(tangent);

            float dotNormal1 = this->velocity.DotProduct(normal);
            float dotNormal2 = 0;
            if (ent->isKinematic()) {
                Vector2 s = ent->velocity * -1.0f;
                dotNormal2 = s.DotProduct(normal);
            }
            else {
                dotNormal2 = ent->velocity.DotProduct(normal);
            }

            float totalMass = (this->mass + ent->mass);
            float m1 = this->bounciness * (dotNormal1 * (this->mass - ent->mass) + (2.0f * ent->mass * dotNormal2)) / totalMass;
            float m2 = ent->getBounciness() * (dotNormal2 * (ent->mass - this->mass) + (2.0f * this->mass * dotNormal1)) / totalMass;

            this->velocity.Set(tangent.x * dotTan1 + normal.x * m1, tangent.y * dotTan1 + normal.y * m1);
            ent->velocity.Set(tangent.x * dotTan2 + normal.x * m2, tangent.y * dotTan2 + normal.y * m2);
        }
        else if (ent->type == BOX) {
            EntityBox* col = (EntityBox*)ent;

            float angleRadians = ent->rotation * ANGLE_TO_RADIANS;

            float cos = std::cosf(angleRadians);
            float sin = std::sinf(angleRadians);

            float unrotatedCircleX = cos * (this->position.x - ent->position.x) - sin * (this->position.y - ent->position.y) + ent->position.x;
            float unrotatedCircleY = sin * (this->position.x - ent->position.x) + cos * (this->position.y - ent->position.y) + ent->position.y;

            // temporary variables to set edges for testing
            float testX = this->position.x;
            float testY = this->position.y;

            // which edge is closest?
            if (unrotatedCircleX < ent->position.x - col->getLength() * 0.5f) testX = ent->position.x - col->getLength() * 0.5f;      // test left edge
            else if (unrotatedCircleX > ent->position.x + col->getLength() * 0.5f) testX = ent->position.x + col->getLength() * 0.5f;   // right edge
            if (unrotatedCircleY < ent->position.y - col->getWidth() * 0.5f)         testY = ent->position.y - col->getWidth() * 0.5f;      // top edge
            else if (unrotatedCircleY > ent->position.y + col->getWidth() * 0.5f) testY = ent->position.y + col->getWidth() * 0.5f;   // bottom edge

            // get distance from closest edges
            Vector2 difference = Vector2(unrotatedCircleX - testX, unrotatedCircleY - testY);
            float distance_sqr = difference.MagnitudeSqr();

            // if the distance is less than the radius, collision!
            if (distance_sqr <= (radius * radius)) {

            }
        }
    }
}