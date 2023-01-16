#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "../Vector2.h"
#include <iostream>
#include "../Common.h"



class Entity
{
	public:
		Entity();
		Entity(Vector2 position);
		Entity(Vector2 position, float rotation);
		~Entity();
		virtual void Update() = 0;
		void CheckCollisions(std::vector<Entity*> ents);
		virtual void Collision(Entity* ent) = 0;
		virtual void Render(GLuint shaderProgram, double frameDelta) = 0;
		float getBounciness();
		Vector2 position;
		Vector2 velocity;
		Vector2 force;
		float rotation;
		float mass;
		float color[3];
		EntityType type;
	private:
		virtual void PrepareModel() = 0;
	protected:
		VAO vao;
		bool  usePhysics = true;
		float bounciness = 0.85f;
		float friction = 0.05f;
		float deactivation = 0.05f;
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
	void Collision(Entity* ent) override;
private:
	void PrepareModel() override;
	int numTriangles = 20;
	float radius;
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
	void Collision(Entity* ent) override;
private:
	void PrepareModel() override;
	float width;
	float length;
};


#endif

