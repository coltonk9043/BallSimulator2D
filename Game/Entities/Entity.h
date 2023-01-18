#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "../Vector2.h"
#include <iostream>
#include "../Common.h"
#include "../Mesh.h"


class Entity
{
	public:
		Entity();
		Entity(Vector2 position, Mesh* mesh);
		Entity(Vector2 position, float rotation, Mesh* mesh);
		~Entity();
		void Update();
		void CheckCollisions(std::vector<Entity*> ents);
		virtual void Collision(Entity* ent) = 0;
		virtual void Render(GLuint shaderProgram, double frameDelta);
		float getBounciness();
		bool isKinematic();
		void setKinematic(bool state);
		Vector2 position;
		Vector2 velocity;
		Vector2 force;
		float rotation;
		Vector2 scale;
		float mass;
		float color[3];
		EntityType type;
	protected:
		Mesh* mesh;
		bool kinematic = false;
		float bounciness = 0.85f;
		float friction = 0.05f;
		float deactivation = 0.05f;
		virtual void PreUpdate() = 0;
		virtual void PostUpdate() = 0;
};

class EntityCircle : public Entity
{
public:
	EntityCircle();
	EntityCircle(Vector2 position, Mesh* mesh);
	EntityCircle(Vector2 position, float rotation, Mesh* mesh);
	~EntityCircle();
	void Collision(Entity* ent) override;
private:
	void PreUpdate() override;
	void PostUpdate() override;
	int numTriangles = 20;
	float radius;
};

class EntityBox : public Entity
{
public:
	EntityBox();
	EntityBox(Vector2 position, Mesh* mesh);
	EntityBox(Vector2 position, float rotation, Mesh* mesh);
	~EntityBox();
	void Collision(Entity* ent) override;
	float getWidth();
	float getLength();
private:
	void PreUpdate() override;
	void PostUpdate() override;
	float width = 1.0f;
	float length = 1.0f;
};


#endif

