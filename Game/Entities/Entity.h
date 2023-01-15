#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "../Vector2.h"
#include <iostream>
#include "../Common.h"


class Collider;
struct CollisionInfo;

class Entity
{
	public:
		Entity();
		Entity(Vector2 position);
		Entity(Vector2 position, float rotation);
		~Entity();
		virtual void Update() = 0;
		void CheckCollisions(std::vector<Entity*> ents);
		virtual void Render(GLuint shaderProgram, double frameDelta) = 0;
		Collider* GetCollider();
		Vector2 position;
		Vector2 velocity;
		Vector2 force;
		float rotation;
		float mass;
		float color[3];
	private:
		virtual void PrepareModel() = 0;
	protected:
		VAO vao;
		bool  usePhysics = true;
		Collider* collider;
};

class EntityCircle : public Entity
{
public:
	EntityCircle();
	EntityCircle(Vector2 position);
	EntityCircle(Vector2 position, float rotation);
	~EntityCircle();
	void Update() override;
	void Render(GLuint shaderProgram, double frameDelta) override;
private:
	void PrepareModel() override;
	int numTriangles = 20;
};

class EntityBox : public Entity
{
public:
	EntityBox();
	EntityBox(Vector2 position);
	EntityBox(Vector2 position, float rotation);
	~EntityBox();
	void Update() override;
	void Render(GLuint shaderProgram, double frameDelta) override;
private:
	void PrepareModel() override;
};


#endif

