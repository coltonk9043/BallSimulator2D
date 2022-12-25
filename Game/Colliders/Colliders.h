#pragma once

#ifndef COLLIDERS_H
#define COLLIDERS_H

#include "../Entity.h"

class Collider
{
public:
	Collider(Entity* ent);
	~Collider();
	bool enabled;
	Entity* entity;
protected:
	float bounciness;
	float friction;
};

class CircleCollider : Collider
{
public:
	CircleCollider(Entity* ent, float radius);
	~CircleCollider();
protected:
	float radius;
}

class BoxCollider : Collider
{
public:
	BoxCollider(Entity* ent, float radius);
	~BoxCollider();
protected:
	float length;
	float width;
}

#endif