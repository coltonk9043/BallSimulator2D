/*
Colton Kennedy
A class acting as a 2 Dimensional Vector
1/16/2023
*/ 

#include "Vector2.h"

/// <summary>
/// Vector2 Empty Constructor
/// </summary>
Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
}

/// <summary>
/// Constructor that takes x and y coordinates.
/// </summary>
/// <param name="x">X position</param>
/// <param name="y">Y position</param>
Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

/// <summary>
/// Adds this Vector to another and returns the result.
/// </summary>
/// <param name="obj">The Vector being added.</param>
/// <returns>The sum of both vectors.</returns>
Vector2 Vector2::operator+(Vector2 const& obj) const {
	Vector2 vec;
	vec.x = x + obj.x;
	vec.y = y + obj.y;
	return vec;
}

/// <summary>
/// Substracts this Vector by another and returns the result.
/// </summary>
/// <param name="obj">The Vector being subtracted.</param>
/// <returns>The difference of both Vectors.</returns>
Vector2 Vector2::operator-(Vector2 const& obj) const {
	Vector2 vec;
	vec.x = x - obj.x;
	vec.y = y - obj.y;
	return vec;
}

/// <summary>
/// Multiplies this Vector by another and returns the result.
/// </summary>
/// <param name="obj">The Vector being multiplied.</param>
/// <returns>The product of both Vectors.</returns>
Vector2 Vector2::operator*(Vector2 const& obj) const {
	Vector2 vec;
	vec.x = x * obj.x;
	vec.y = y * obj.y;
	return vec;
}

/// <summary>
/// Divides this Vector by another and returns the result
/// </summary>
/// <param name="obj">The Vector acting as the divisor.</param>
/// <returns>The quotient of both Vectors.</returns>
Vector2 Vector2::operator/(Vector2 const& obj) const {
	Vector2 vec;
	vec.x = x / obj.x;
	vec.y = y / obj.y;
	return vec;
}

/// <summary>
/// Adds a value to both coordinates.
/// </summary>
/// <param name="val">The value being added.</param>
/// <returns>The sum of this Vector and the value.</returns>
Vector2 Vector2::operator+(float const& val) const {
	Vector2 vec;
	vec.x = x + val;
	vec.y = y + val;
	return vec;
}

/// <summary>
/// Subtracts a value from both coordinates.
/// </summary>
/// <param name="val">The value being subtracted.</param>
/// <returns>The different of this Vector and the value.</returns>
Vector2 Vector2::operator-(float const& val) const {
	Vector2 vec;
	vec.x = x - val;
	vec.y = y - val;
	return vec;
}

/// <summary>
/// Multiplied a vector by a scalar.
/// </summary>
/// <param name="val">The scalar being multiplied.</param>
/// <returns>The product of the Vector and the scalar.</returns>
Vector2 Vector2::operator*(float const& val) const {
	Vector2 vec;
	vec.x = x * val;
	vec.y = y * val;
	return vec;
}

/// <summary>
/// Divides a vector by a scalar.
/// </summary>
/// <param name="val">The scalar being divded.</param>
/// <returns>The quotient of the Vector and the scalar.</returns>
Vector2 Vector2::operator/(float const& val) const {
	Vector2 vec;
	vec.x = x / val;
	vec.y = y / val;
	return vec;
}

/// <summary>
/// Multiplied a vector by a scalar.
/// </summary>
/// <param name="val">The scalar being multiplied.</param>
/// <returns>The product of the Vector and the scalar.</returns>
Vector2 Vector2::operator*=(float const& val) const {
	Vector2 vec;
	vec.x = x * val;
	vec.y = y * val;
	return vec;
}

/// <summary>
/// Sets the coordinate of the Vector.
/// </summary>
/// <param name="x">The X coordinate to set.</param>
/// <param name="y">The Y coordinate to set.</param>
void Vector2::Set(float x, float y) {
	this->x = x;
	this->y = y;
}

/// <summary>
/// Returns the Vector as an array.
/// </summary>
/// <returns>Array representation of the Vector (x,y).</returns>
float* Vector2::AsArray() {
	float buffer[2];
	buffer[0] = this->x;
	buffer[1] = this->y;
	return buffer;
}

/// <summary>
/// Calculates the normalization of the Vector.
/// </summary>
/// <returns>The normal of the Vector.</returns>
Vector2 Vector2::Normalized() {
	double mag = 1.0 / sqrtf(x*x + y*y);
	return Vector2(x * mag, y * mag);
}

/// <summary>
/// Rotates a Vector by an angle.
/// </summary>
/// <param name="angle">The angle of which to rotate.</param>
void Vector2::Rotate(float angle)
{
	float xt = (this->x * cosf(angle)) - (this->y * sinf(angle));
	float yt = (this->y * cosf(angle)) + (this->x * sinf(angle));
	this->x = xt;
	this->y = yt;
}

/// <summary>
/// Normalizes the Vector.
/// </summary>
void Vector2::Normalize()
{
	double mag = 1.0 / sqrtf(x*x + y*y);
	this->x = x * mag;
	this->y = y * mag;
}

/// <summary>
/// Calculates the Magnitude of the Vector.
/// </summary>
/// <returns>The magnitude of the Vector.</returns>
float Vector2::Magnitude()
{
	return sqrtf(this->x * this->x + this->y * this->y);
}

/// <summary>
/// Calculates the Square Magnitude of the Vector.
/// </summary>
/// <returns>The Square Magnitude of the Vector.</returns>
float Vector2::MagnitudeSqr() {
	return (this->x * this->x + this->y * this->y);
}

/// <summary>
/// Returns the Dot Product of this and another Vector.
/// </summary>
/// <param name="obj">Vector to perform the Dot Product with.</param>
/// <returns>The Dot Product of two Vectors.</returns>
float Vector2::DotProduct(const Vector2& obj) const
{
	return (this->x * obj.x) + (this->y * obj.y);
}

/// <summary>
/// Returns the Cross Product of this and another Vector.
/// </summary>
/// <param name="obj">Vector to perform the Cross Product with.</param>
/// <returns>The Cross Product of two Vectors.</returns>
float Vector2::CrossProduct(const Vector2& obj) const
{
	return (this->x * obj.y) - (this->y * obj.x);
}