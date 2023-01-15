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

float CircleCollider::getRadius() {
	return this->radius;
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
	else if (ent->GetCollider()->GetType() == BOX) {
		BoxCollider* col = (BoxCollider*)ent->GetCollider();

	/*	Vector2 A = ent->position + Vector2(-col->getLength(), col->getWidth());
		Vector2 B = ent->position + Vector2(col->getLength(), col->getWidth());
		Vector2 C = ent->position + Vector2(col->getLength(), -col->getWidth());
		Vector2 D = ent->position + Vector2(-col->getLength(), -col->getWidth());

		Vector2 timestepped_velocity = (this->entity->velocity * TIMESTEP);

		Vector2 AP = this->entity->position - A;
		Vector2 AB = A - B;
		Vector2 AD = this->entity->position - D;

		float AP_AB = AP.DotProduct(AB);
		float AB_AB = AB.DotProduct(AB);

		float AP_AD = AP.DotProduct(AD);
		float AD_AD = AD.DotProduct(AD);

		if (0 <= AP_AB <= AB_AB && 0 <= AP_AD <= AD_AD) {
			collisionInfo.collidedWith = ent;
			float totalMass = (this->entity->mass + ent->mass);
			float newVelocityX1 = (this->entity->velocity.x * (this->entity->mass - ent->mass) + (2 * ent->mass * ent->velocity.x)) / totalMass;
			float newVelocityY1 = (this->entity->velocity.y * (this->entity->mass - ent->mass) + (2 * ent->mass * ent->velocity.y)) / totalMass;
			float newVelocityX2 = (ent->velocity.x * (ent->mass - this->entity->mass) + (2 * this->entity->mass * this->entity->velocity.x)) / totalMass;
			float newVelocityY2 = (ent->velocity.y * (ent->mass - this->entity->mass) + (2 * this->entity->mass * this->entity->velocity.y)) / totalMass;

			this->entity->velocity.Set(newVelocityX1, newVelocityY1);
			ent->velocity.Set(newVelocityX2, newVelocityY2);
		}*/
	}
	return collisionInfo;
}

// Box COllider
BoxCollider::BoxCollider(Entity* ent, float length, float width) : Collider(ent) {
	this->length = length;
	this->width = width;
	this->type = BOX;
}

BoxCollider::~BoxCollider() {

}

CollisionInfo BoxCollider::CheckCollision(Entity* ent) {
	CollisionInfo collisionInfo;
	return collisionInfo;
}

float BoxCollider::getWidth() {
	return this->width;
}

float BoxCollider::getLength() {
	return this->length;
}
