#pragma once

#ifndef __COLLIDERS_H__
#define __COLLIDERS_H__

#include "../Entities/Entity.h"
#include <cmath>

using namespace std;

enum CollisionType {
	CIRCLE,
	BOX,
	POLYGON
};

struct CollisionInfo {
	Entity* collidedWith;
	Vector2 pointOfCollision;
	Vector2 relativeVelocity;
};

class Collider
{
public:
	Collider(Entity* ent);
	~Collider();
	virtual CollisionInfo CheckCollision(Entity* target) = 0;
	bool enabled;
	Entity* entity;
	CollisionType GetType();
	float getBounciness();
	float getFriction();
protected:
	float bounciness;
	float friction;
	CollisionType type;
};

class CircleCollider : public Collider
{
public:
	CircleCollider(Entity* ent, float radius);
	~CircleCollider();
	CollisionInfo CheckCollision(Entity* target) override;
	float getRadius();
protected:
	float radius;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(Entity* ent, float length, float width);
	~BoxCollider();
	CollisionInfo CheckCollision(Entity* target) override;
	float getWidth();
	float getLength();
protected:
	float length;
	float width;
};

#endif