#include "Matrix4.h"

#include "Common.h"

Matrix4::Matrix4() {
    Identity();
}

float* Matrix4::AsArray() {
    return data;
}

void Matrix4::Identity() {
    for (int i = 0; i < 16; i++) {
        data[i] = 0.0f;
    }
    data[0] = 1.0f;
    data[5] = 1.0f;
    data[10] = 1.0f;
    data[15] = 1.0f;
}

void Matrix4::Set(float* matrix) {
    for (int i = 0; i < 16; i++) {
        data[i] = matrix[i];
    }
}

void Matrix4::Translate(float x, float y, float z) {
    Matrix4 copy;
    Matrix4 result;
    result.Identity();

    result.data[12] = x;
    result.data[13] = y;
    result.data[14] = z;

    copy = (*this) * result;
    this->Set(copy.data);
}

void Matrix4::Scale(float x, float y, float z) {
    Matrix4 copy;
    Matrix4 result;
    result.Identity();

    result.data[0] = x;
    result.data[5] = y;
    result.data[10] = z;

    copy = (*this) * result;
    this->Set(copy.data);
}

void Matrix4::Rotate(float x, float y, float z) {
    if (x != 0.0f) {
        this->RotateX(x);
    }
    if (y != 0.0f) {
        this->RotateY(y);
    }
    if (z != 0.0f) {
        this->RotateZ(z);
    }
}

void Matrix4::RotateX(float x) {
    float cos = std::cosf(x * ANGLE_TO_RADIANS);
    float sin = std::sinf(x * ANGLE_TO_RADIANS);

    Matrix4 copy;
    Matrix4 result;
    result.Identity();

    result.data[5] = cos;
    result.data[6] = sin;
    result.data[9] = -sin;
    result.data[10] = cos;

    copy = (*this) * result;
    this->Set(copy.data);
}

void Matrix4::RotateY(float y) {
    float cos = std::cosf(y * ANGLE_TO_RADIANS);
    float sin = std::sinf(y * ANGLE_TO_RADIANS);

    Matrix4 copy;
    Matrix4 result;
    result.Identity();

    result.data[0] = cos;
    result.data[2] = -sin;
    result.data[8] = sin;
    result.data[10] = cos;

    copy = (*this) * result;
    this->Set(copy.data);
}
void Matrix4::RotateZ(float z) {
    float cos = std::cosf(z * ANGLE_TO_RADIANS);
    float sin = std::sinf(z * ANGLE_TO_RADIANS);

    Matrix4 copy;
    Matrix4 result;
    result.Identity();

    result.data[0] = cos;
    result.data[1] = sin;
    result.data[4] = -sin;
    result.data[5] = cos;

    copy = (*this) * result;
    this->Set(copy.data);
}

Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far) {
	Matrix4 m;

    m.Identity();

    m.data[0] = 2.0f / (right - left);
    m.data[5] = 2.0f / (top - bottom);
    m.data[10] = -2.0f / (far - near);
    m.data[12] = -(right + left) / (right - left);
    m.data[13] = -(top + bottom) / (top - bottom);
    m.data[14] = -(far + near) / (far - near);

    return m;
}

Matrix4 Matrix4::operator* (const Matrix4& m) const {
    Matrix4 result;

    result.data[0] = ((data[0] * m.data[0]) + (data[1] * m.data[4]) + (data[2] * m.data[8]) + (data[3] * m.data[12]));
    result.data[1] = ((data[0] * m.data[1]) + (data[1] * m.data[5]) + (data[2] * m.data[9]) + (data[3] * m.data[13]));
    result.data[2] = ((data[0] * m.data[2]) + (data[1] * m.data[6]) + (data[2] * m.data[10]) + (data[3] * m.data[14]));
    result.data[3] = ((data[0] * m.data[3]) + (data[1] * m.data[7]) + (data[2] * m.data[11]) + (data[3] * m.data[15]));

    result.data[4] = ((data[4] * m.data[0]) + (data[5] * m.data[4]) + (data[6] * m.data[8]) + (data[7] * m.data[12]));
    result.data[5] = ((data[4] * m.data[1]) + (data[5] * m.data[5]) + (data[6] * m.data[9]) + (data[7] * m.data[13]));
    result.data[6] = ((data[4] * m.data[2]) + (data[5] * m.data[6]) + (data[6] * m.data[10]) + (data[7] * m.data[14]));
    result.data[7] = ((data[4] * m.data[3]) + (data[5] * m.data[7]) + (data[6] * m.data[11]) + (data[7] * m.data[15]));

    result.data[8] = ((data[8] * m.data[0]) + (data[9] * m.data[4]) + (data[10] * m.data[8]) + (data[11] * m.data[12]));
    result.data[9] = ((data[8] * m.data[1]) + (data[9] * m.data[5]) + (data[10] * m.data[9]) + (data[11] * m.data[13]));
    result.data[10] = ((data[8] * m.data[2]) + (data[9] * m.data[6]) + (data[10] * m.data[10]) + (data[11] * m.data[14]));
    result.data[11] = ((data[8] * m.data[3]) + (data[9] * m.data[7]) + (data[10] * m.data[11]) + (data[11] * m.data[15]));

    result.data[12] = ((data[12] * m.data[0]) + (data[13] * m.data[4]) + (data[14] * m.data[8]) + (data[15] * m.data[12]));
    result.data[13] = ((data[12] * m.data[1]) + (data[13] * m.data[5]) + (data[14] * m.data[9]) + (data[15] * m.data[13]));
    result.data[14] = ((data[12] * m.data[2]) + (data[13] * m.data[6]) + (data[14] * m.data[10]) + (data[15] * m.data[14]));
    result.data[15] = ((data[12] * m.data[3]) + (data[13] * m.data[7]) + (data[14] * m.data[11]) + (data[15] * m.data[15]));

    return result;
}