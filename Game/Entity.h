#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"
#include "Common.h"
#include <iostream>

class Entity
{
	public:
		Entity();
		Entity(Vector2 position);
		Entity(Vector2 position, float rotation);
		~Entity();
		void Update();
		void Render(float frameDelta);
		Vector2 position;
		Vector2 velocity;
		Vector2 force;
		float rotation;
		float mass;
	private:
		VAO vao;
		float radius = 5.0f;
		bool  usePhysics = true;
		void PrepareModel();
	protected:
		int numTriangles = 20;
};

#endif

