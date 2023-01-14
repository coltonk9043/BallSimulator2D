#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"
#include <iostream>
#include "Common.h"

class Collider;
struct CollisionInfo;

class Entity
{
	public:
		Entity();
		Entity(Vector2 position);
		Entity(Vector2 position, float rotation);
		~Entity();
		void Update();
		void CheckCollisions(std::vector<Entity*> ents);
		void Render(double frameDelta);
		void OnCollide(CollisionInfo collisionInfo);
		Collider* GetCollider();
		Vector2 position;
		Vector2 velocity;
		Vector2 force;
		float rotation;
		float mass;
		float color[3];
	private:
		VAO vao;
		float radius = 20.0f;
		bool  usePhysics = true;
		void PrepareModel();
	protected:
		int numTriangles = 10;
		Collider* collider;
};

#endif

