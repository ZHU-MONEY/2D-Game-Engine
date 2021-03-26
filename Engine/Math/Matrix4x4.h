#pragma once
#include "Vector4.h"

class Matrix4x4
{
public:
    explicit Matrix4x4();
    explicit Matrix4x4(float i_11, float i_12, float i_13, float i_14,
        float i_21, float i_22, float i_23, float i_24,
        float i_31, float i_32, float i_33, float i_34,
        float i_41, float i_42, float i_43, float i_44);
    ~Matrix4x4();

    void Set(float i_11, float i_12, float i_13, float i_14,
        float i_21, float i_22, float i_23, float i_24,
        float i_31, float i_32, float i_33, float i_34,
        float i_41, float i_42, float i_43, float i_44);

    // copy constructor
    Matrix4x4(const Matrix4x4& copy);
    // copy assignment operator
    Matrix4x4& operator=(const Matrix4x4& other);

    // get the determinant
    float GetDeterminant() const;

    // invert matrix
    void Invert();
    // return an inverse of this matrix
    Matrix4x4 GetInverse() const;

    // transpose this matrix
    void Transpose();
    // return a transpose of this matrix
    Matrix4x4 GetTranspose() const;

    // equality check
    bool operator==(const Matrix4x4& other) const;

    // multiply a matrix with this matrix viz. this * rightMatrix
    Matrix4x4 Multiply(const Matrix4x4& rightMatrix) const;
    // multiply a Vector4 with this matrix viz. i_vec4 * this
    Vector4 MultiplyLeft(const Vector4& leftVector) const;
    // multiply a Vector4 with this matrix viz. this * i_vec4
    Vector4 MultiplyRight(const Vector4& rightVector) const;

    // translation matrix
    static Matrix4x4 GetTranslation(const Vector2& translation);

    // rotation matrices
    static Matrix4x4 GetRotationX(const float radians);
    static Matrix4x4 GetRotationY(const float radians);
    static Matrix4x4 GetRotationZ(const float radians);

    // scaling matrix
    static Matrix4x4 GetScale(const float scale);

//#ifdef BUILD_DEBUG
//    void Print() const;
//#endif

    static const Matrix4x4 IDENTITY;
    static const Matrix4x4 ZERO;

private:
    float       f11, f12, f13, f14;
    float       f21, f22, f23, f24;
    float       f31, f32, f33, f34;
    float       f41, f42, f43, f44;

}; // class Matrix4x4

// matrix multiplication
inline Matrix4x4 operator*(const Matrix4x4& leftMatrix, const Matrix4x4& rightMatrix) 
{
    return leftMatrix.Multiply(rightMatrix);
};
// V = M * V
inline Vector4 operator*(const Matrix4x4& leftMatrix, const Vector4& rightMatrix)
{
    return leftMatrix.MultiplyRight(rightMatrix);
};
// V = V * M
inline Vector4 operator*(const Vector4& leftMatrix, const Matrix4x4& rightMatrix)
{
    return rightMatrix.MultiplyLeft(leftMatrix);
};