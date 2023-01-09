#include "Vector2.h"

Vector2::Vector2() {
	this->x = 0;
	this->y = 0;
}

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator+(Vector2 const& obj) const {
	Vector2 vec;
	vec.x = x + obj.x;
	vec.y = y + obj.y;
	return vec;
}

Vector2 Vector2::operator-(Vector2 const& obj) const {
	Vector2 vec;
	vec.x = x - obj.x;
	vec.y = y - obj.y;
	return vec;
}

Vector2 Vector2::operator*(Vector2 const& obj) const {
	Vector2 vec;
	vec.x = x * obj.x;
	vec.y = y * obj.y;
	return vec;
}

Vector2 Vector2::operator/(Vector2 const& obj) const {
	Vector2 vec;
	vec.x = x / obj.x;
	vec.y = y / obj.y;
	return vec;
}

Vector2 Vector2::operator+(float const& val) const {
	Vector2 vec;
	vec.x = x + val;
	vec.y = y + val;
	return vec;
}

Vector2 Vector2::operator-(float const& val) const {
	Vector2 vec;
	vec.x = x - val;
	vec.y = y - val;
	return vec;
}

Vector2 Vector2::operator*(float const& val) const {
	Vector2 vec;
	vec.x = x * val;
	vec.y = y * val;
	return vec;
}

Vector2 Vector2::operator*=(float const& val) const {
	Vector2 vec;
	vec.x = x * val;
	vec.y = y * val;
	return vec;
}

Vector2 Vector2::operator/(float const& val) const {
	Vector2 vec;
	vec.x = x / val;
	vec.y = y / val;
	return vec;
}

Vector2 Vector2::Normalized() {
	float mag = sqrtf(this->x * this->x + this->y * this->y);
	return Vector2(this->x / mag, this->y / mag);
}

float* Vector2::AsArray() {
	float buffer[2];
	buffer[0] = this->x;
	buffer[1] = this->y;
	return buffer;
}

void Vector2::Rotate(float angle)
{
	float xt = (this->x * cosf(angle)) - (this->y * sinf(angle));
	float yt = (this->y * cosf(angle)) + (this->x * sinf(angle));
	this->x = xt;
	this->y = yt;
}

void Vector2::Normalize()
{
	float mag = sqrtf(this->x * this->x + this->y * this->y);
	this->x = this->x / mag;
	this->y = this->y / mag;
}

void Vector2::Set(float x, float y) {
	this->x = x;
	this->y = y;
}

float Vector2::CrossProduct(const Vector2& obj) const
{
	return (this->x * obj.y) - (this->y * obj.x);
}

float Vector2::Magnitude()
{
	return sqrtf(this->x * this->x + this->y * this->y);
}

float Vector2::DotProduct(const Vector2& obj) const
{
	return (this->x * obj.x) + (this->y * obj.y);
}