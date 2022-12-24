#pragma once

#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <vector>
class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	float x;
	float y;

	Vector2 operator+ (Vector2 const& obj) const;
	Vector2 operator- (Vector2 const& obj) const;
	Vector2 operator* (Vector2 const& obj) const;
	Vector2 operator/ (Vector2 const& obj) const;

	Vector2 operator+ (float const& val) const;
	Vector2 operator- (float const& val) const;
	Vector2 operator* (float const& val) const;
	Vector2 operator/ (float const& val) const;

	Vector2 Normalized();

	void Normalize();
    void Rotate(float angle);
	void Set(float x, float y);
    float CrossProduct(const Vector2& rhs) const;
    float Magnitude();
	float DotProduct(const Vector2& rhs) const;

	float* AsArray();
};

#endif