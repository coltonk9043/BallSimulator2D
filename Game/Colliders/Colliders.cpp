#include "Colliders.h"


// Abstract Collider
Collider::Collider(Entity* ent) {
	this->entity = ent;
	this->bounciness = 0.82f;
	this->friction = 0.5f;
}

Collider::~Collider() {

}

float Collider::getBounciness() {
	return this->bounciness;
}

float Collider::getFriction() {
	return this->friction;
}

CollisionType Collider::GetType() { return this->type; }

// Circle Collider
CircleCollider::CircleCollider(Entity* ent, float radius) : Collider(ent){
	this->radius = radius;
	this->type = CIRCLE;
}

CircleCollider::~CircleCollider() {

}

CollisionInfo CircleCollider::CheckCollision(Entity* ent) {
	CollisionInfo collisionInfo;
	if (ent->GetCollider()->GetType() == CIRCLE) {
		CircleCollider* col = (CircleCollider*)ent->GetCollider();

		// Gets the difference in entity positions as distance.
		Vector2 difference = ent->position - this->entity->position;
		double distance = difference.Magnitude();

		// Gets the sum of the radius and subtracts it from the distance.
		float sum_radius = col->radius + this->radius;
		distance -= sum_radius;

		// Get the velocity relative to the timestep.
		Vector2 timestepped_velocity = (this->entity->velocity * TIMESTEP);

		// If the velocity is less than the distance between the radii of the two circles, a collision is not occuring.
		if (timestepped_velocity.Magnitude() < distance) return collisionInfo;
		
		// Calculate whether the velocity is facing the object. If not, return.
		Vector2 normalized = timestepped_velocity.Normalized();
		double dot = normalized.DotProduct(difference);
		if (dot <= 0) return collisionInfo;
		
		// Get the magnitude of the difference between the entities position.
		double length = difference.Magnitude();
		double distance_sqr = (length * length) - (dot * dot);
		float sum_radius_sqr = sum_radius * sum_radius;
		if (distance_sqr >= sum_radius_sqr) return collisionInfo;
		

		double T = sum_radius_sqr - distance_sqr;
		if (T < 0) return collisionInfo;
		

		// Therefore the distance the circle has to travel along
		// movevec is D - sqrt(T)
		double velocity_length = dot - sqrt(T);

		// Get the magnitude of the movement vector
		double mag = timestepped_velocity.Magnitude();

		// Finally, make sure that the distance A has to move
		// to touch B is not greater than the magnitude of the
		// movement vector.
		if (mag < distance) {
			return collisionInfo;
		}

		// Set the length of the movevec so that the circles will just
		// touch
		Vector2 normalized_vel = this->entity->velocity.Normalized();
		normalized_vel = normalized_vel * velocity_length;

		collisionInfo.collidedWith = ent;
		collisionInfo.pointOfCollision = Vector2(((this->entity->position.x * col->radius) + (ent->position.x * this->radius)) / sum_radius,
		((this->entity->position.y * col->radius) + (ent->position.y * this->radius)) / sum_radius);
		
		float totalMass = (this->entity->mass + ent->mass);
		float newVelocityX1 = (this->entity->velocity.x * (this->entity->mass - ent->mass) + (2 * ent->mass * ent->velocity.x)) / totalMass;
		float newVelocityY1 = (this->entity->velocity.y * (this->entity->mass - ent->mass) + (2 * ent->mass * ent->velocity.y)) / totalMass;
		float newVelocityX2 = (ent->velocity.x * (ent->mass - this->entity->mass) + (2 * this->entity->mass * this->entity->velocity.x)) / totalMass;
		float newVelocityY2 = (ent->velocity.y * (ent->mass - this->entity->mass) + (2 * this->entity->mass * this->entity->velocity.y)) / totalMass;
	
		this->entity->velocity.Set(newVelocityX1, newVelocityY1);
		ent->velocity.Set(newVelocityX2, newVelocityY2);
	}
	return collisionInfo;
}

//// Static Collision
//Vector2 distance = this->entity->position - ent->position;
//float distSqr = distance.DotProduct(distance);
//
//if (distSqr > radius * radius + col->radius * col->radius) collisionInfo.collidedWith = nullptr;
//else {
//	collisionInfo.collidedWith = ent;
//
//	float totalRadius = (this->radius + col->radius);
//	collisionInfo.pointOfCollision = Vector2(((this->entity->position.x * col->radius) + (ent->position.x * this->radius)) / totalRadius,
//		((this->entity->position.y * col->radius) + (ent->position.y * this->radius)) / totalRadius);
//
//	float totalMass = (this->entity->mass + ent->mass);
//	float newVelocityX1 = (this->entity->velocity.x * (this->entity->mass - ent->mass) + (2 * ent->mass * ent->velocity.x)) / totalMass;
//	float newVelocityY1 = (this->entity->velocity.y * (this->entity->mass - ent->mass) + (2 * ent->mass * ent->velocity.y)) / totalMass;
//	float newVelocityX2 = (ent->velocity.x * (ent->mass - this->entity->mass) + (2 * this->entity->mass * this->entity->velocity.x)) / totalMass;
//	float newVelocityY2 = (ent->velocity.y * (ent->mass - this->entity->mass) + (2 * this->entity->mass * this->entity->velocity.y)) / totalMass;
//
//	this->entity->velocity.Set(newVelocityX1, newVelocityY1);
//	ent->velocity.Set(newVelocityX2, newVelocityY2);
//
//	this->entity->position = this->entity->position + (this->entity->velocity * TIMESTEP);
//
//}
//return collisionInfo;

//// Dynamic Collision
//float A1 = this->entity->velocity.y;
//float B1 = -this->entity->velocity.x;
//double C1 = A1 * this->entity->position.x + B1 * this->entity->position.y;
//double C2 = -B1 * ent->position.x + A1 * ent->position.y;
//double det = (A1 * A1) - (-B1 * B1);
//Vector2 d;
//
//if (det != 0) {
//	d.Set((float)((A1 * C1 - B1 * C2) / det), (float)((A1 * C2 - -B1 * C1) / det));
//}
//else {
//	d.Set(ent->position.x, ent->position.y);
//}
//
//double closestdistsq = pow(ent->position.x - d.x, 2) + pow((ent->position.y - d.y), 2);
//if (closestdistsq <= pow(this->radius + col->radius, 2)) {
//	double backdist = sqrt(pow(this->radius + col->radius, 2) - closestdistsq);
//	double movementvectorlength = sqrt(pow(this->entity->velocity.x, 2) + pow(this->entity->velocity.y, 2));
//
//	Vector2 pointOfCollision(d.x - backdist * (this->entity->velocity.x / movementvectorlength)
//		, d.y - backdist * (this->entity->velocity.y / movementvectorlength));
//
//	collisionInfo.collidedWith = ent;
//	collisionInfo.pointOfCollision = pointOfCollision;
//
//	double collisiondist = sqrt(pow(ent->position.x - d.x, 2) + pow(ent->position.y - d.y, 2));
//	double n_x = (ent->position.x - d.x) / collisiondist;
//	double n_y = (ent->position.y - d.y) / collisiondist;
//	double p = 2 * (this->entity->velocity.x * n_x + this->entity->velocity.y * n_y) /
//		(this->entity->mass + ent->mass);
//	double w_x = this->entity->velocity.x - p * this->entity->mass * n_x - p * ent->mass * n_x;
//	double w_y = ent->velocity.y - p * this->entity->mass * n_y - p * ent->mass * n_y;
//
//	this->entity->velocity.Set(w_x, w_y);
//}
//else {
//	collisionInfo.collidedWith = nullptr;
//}