#pragma once

#ifndef __COLLIDERS_H__
#define __COLLIDERS_H__

#include "../Entity.h"
#include <cmath>

using namespace std;

enum CollisionType {
	CIRCLE,
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
protected:
	float radius;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(Entity* ent, float radius);
	~BoxCollider();
	CollisionInfo CheckCollision(Entity* target) override;
protected:
	float length;
	float width;
};

#endif