#pragma once
class Matrix4
{
public:
	Matrix4();
	~Matrix4() = default;
	float* AsArray();
	void Identity();
	void Set(float* matrix);
	void Translate(float x, float y, float z);
	void Scale(float x, float y, float z);
	void Rotate(float x, float y, float z);
	void RotateX(float x);
	void RotateY(float y);
	void RotateZ(float z);
	static Matrix4 Orthographic(float left, float right, float bottom, float top, float near, float far);

	// Operator Overloads
	Matrix4 operator* (Matrix4 const& obj) const;
private:
	float data[16];
};

