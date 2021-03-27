#include"Matrix4x4.h"
#include <math.h>

#pragma warning (disable: 26495)

const Matrix4x4 Matrix4x4::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
                                    0.0f, 1.0f, 0.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f, 1.0f);

const Matrix4x4 Matrix4x4::ZERO(0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f);

//do nothing
Matrix4x4::Matrix4x4()
{
}

Matrix4x4::~Matrix4x4()
{}

Matrix4x4::Matrix4x4(float i_11, float i_12, float i_13, float i_14,
                     float i_21, float i_22, float i_23, float i_24,
                     float i_31, float i_32, float i_33, float i_34,
                     float i_41, float i_42, float i_43, float i_44) :
                     f11(i_11), f12(i_12), f13(i_13), f14(i_14),
                     f21(i_21), f22(i_22), f23(i_23), f24(i_24),
                     f31(i_31), f32(i_32), f33(i_33), f34(i_34),
                     f41(i_41), f42(i_42), f43(i_43), f44(i_44)
{
}

void Matrix4x4::Set(float i_11, float i_12, float i_13, float i_14,
    float i_21, float i_22, float i_23, float i_24,
    float i_31, float i_32, float i_33, float i_34,
    float i_41, float i_42, float i_43, float i_44)
{
    f11 = i_11;
    f12 = i_12;
    f13 = i_13;
    f14 = i_14;

    f21 = i_21;
    f22 = i_22;
    f23 = i_23;
    f24 = i_24;

    f31 = i_31;
    f32 = i_32;
    f33 = i_33;
    f34 = i_34;

    f41 = i_41;
    f42 = i_42;
    f43 = i_43;
    f44 = i_44;
}

Matrix4x4::Matrix4x4(const Matrix4x4& copy) :
    f11(copy.f11), f12(copy.f12), f13(copy.f13), f14(copy.f14),
    f21(copy.f21), f22(copy.f22), f23(copy.f23), f24(copy.f24),
    f31(copy.f31), f32(copy.f32), f33(copy.f33), f34(copy.f34),
    f41(copy.f41), f42(copy.f42), f43(copy.f43), f44(copy.f44)
{}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other)
{
    if (this != &other)
    {
        f11 = other.f11;
        f12 = other.f12;
        f13 = other.f13;
        f14 = other.f14;

        f21 = other.f21;
        f22 = other.f22;
        f23 = other.f23;
        f24 = other.f24;

        f31 = other.f31;
        f32 = other.f32;
        f33 = other.f33;
        f34 = other.f34;

        f41 = other.f41;
        f42 = other.f42;
        f43 = other.f43;
        f44 = other.f44;
    }
    return *this;
}

float Matrix4x4::GetDeterminant() const
{
    float a0 = f11 * f22 - f12 * f21;
    float a1 = f11 * f23 - f13 * f21;
    float a2 = f11 * f24 - f14 * f21;
    float a3 = f12 * f23 - f13 * f22;
    float a4 = f12 * f24 - f14 * f22;
    float a5 = f13 * f24 - f14 * f23;
    float b0 = f31 * f42 - f32 * f41;
    float b1 = f31 * f43 - f33 * f41;
    float b2 = f31 * f44 - f34 * f41;
    float b3 = f32 * f43 - f33 * f42;
    float b4 = f32 * f44 - f34 * f42;
    float b5 = f33 * f44 - f34 * f43;

    return (a0 * b5 + a5 * b0 + a3 * b2 + a2 * b3 - a1 * b4 - a4 * b1);
}

void Matrix4x4::Invert()
{
    float a0 = f11 * f22 - f12 * f21;
    float a1 = f11 * f23 - f13 * f21;
    float a2 = f11 * f24 - f14 * f21;
    float a3 = f12 * f23 - f13 * f22;
    float a4 = f12 * f24 - f14 * f22;
    float a5 = f13 * f24 - f14 * f23;
    float b0 = f31 * f42 - f32 * f41;
    float b1 = f31 * f43 - f33 * f41;
    float b2 = f31 * f44 - f34 * f41;
    float b3 = f32 * f43 - f33 * f42;
    float b4 = f32 * f44 - f34 * f42;
    float b5 = f33 * f44 - f34 * f43;

    float det = a0 * b5 + a5 * b0 + a3 * b2 + a2 * b3 - a1 * b4 - a4 * b1;

    if (RoundedEqual(det, 0.0f))
    {   
        // this matrix is not invertable
        return;
    }

    Matrix4x4 adjoin;
    adjoin.f11 =  f22 * b5 - f23 * b4 + f24 * b3;
    adjoin.f12 = -f12 * b5 + f13 * b4 - f14 * b3;
    adjoin.f13 =  f42 * a5 - f43 * a4 + f44 * a3;
    adjoin.f14 = -f32 * a5 + f33 * a4 - f34 * a3;

    adjoin.f21 = -f21 * b5 + f23 * b2 - f24 * b1;
    adjoin.f22 =  f11 * b5 - f13 * b2 + f14 * b1;
    adjoin.f23 = -f41 * a5 + f43 * a2 - f44 * a1;
    adjoin.f24 =  f31 * a5 - f33 * a2 + f34 * a1;

    adjoin.f31 =  f21 * b4 - f22 * b2 + f24 * b0;
    adjoin.f32 = -f11 * b4 + f12 * b2 - f14 * b0;
    adjoin.f33 =  f41 * a4 - f42 * a2 + f44 * a0;
    adjoin.f34 = -f31 * a4 + f32 * a2 - f34 * a0;

    adjoin.f41 = -f21 * b3 + f22 * b1 - f23 * b0;
    adjoin.f42 =  f11 * b3 - f12 * b1 + f13 * b0;
    adjoin.f43 = -f41 * a3 + f42 * a1 - f43 * a0;
    adjoin.f44 =  f31 * a3 - f32 * a1 + f33 * a0;

    // only divide by determinant if determinant is not 1
    if (!RoundedEqual(det, 1.0f))
    {
        float inverse_det = 1.0f / det;

        adjoin.f11 *= inverse_det;
        adjoin.f12 *= inverse_det;
        adjoin.f13 *= inverse_det;
        adjoin.f14 *= inverse_det;

        adjoin.f21 *= inverse_det;
        adjoin.f22 *= inverse_det;
        adjoin.f23 *= inverse_det;
        adjoin.f24 *= inverse_det;

        adjoin.f31 *= inverse_det;
        adjoin.f32 *= inverse_det;
        adjoin.f33 *= inverse_det;
        adjoin.f34 *= inverse_det;

        adjoin.f41 *= inverse_det;
        adjoin.f42 *= inverse_det;
        adjoin.f43 *= inverse_det;
        adjoin.f44 *= inverse_det;
    }

    *this = adjoin;
}

Matrix4x4 Matrix4x4::GetInverse() const
{
    Matrix4x4 inverse(*this);
    inverse.Invert();
    return inverse;
}

void Matrix4x4::Transpose()
{
    float temp = f21;
    f21 = f12;
    f12 = temp;

    temp = f31;
    f31 = f13;
    f13 = temp;

    temp = f41;
    f41 = f14;
    f14 = temp;

    temp = f32;
    f32 = f23;
    f23 = temp;

    temp = f42;
    f42 = f24;
    f24 = temp;

    temp = f43;
    f43 = f34;
    f34 = temp;
}

Matrix4x4 Matrix4x4::GetTranspose() const
{
    Matrix4x4 transpose(*this);
    transpose.Transpose();
    return transpose;
}

bool Matrix4x4::operator==(const Matrix4x4& other) const
{
    if (this == &other)
    {
        return true;
    }

    return !(
        !RoundedEqual(f11, other.f11) ||
        !RoundedEqual(f12, other.f12) ||
        !RoundedEqual(f13, other.f13) ||
        !RoundedEqual(f14, other.f14) ||
        !RoundedEqual(f21, other.f21) ||
        !RoundedEqual(f22, other.f22) ||
        !RoundedEqual(f23, other.f23) ||
        !RoundedEqual(f24, other.f24) ||
        !RoundedEqual(f31, other.f31) ||
        !RoundedEqual(f32, other.f32) ||
        !RoundedEqual(f33, other.f33) ||
        !RoundedEqual(f34, other.f34) ||
        !RoundedEqual(f41, other.f41) ||
        !RoundedEqual(f42, other.f42) ||
        !RoundedEqual(f43, other.f43) ||
        !RoundedEqual(f44, other.f44)
        );
}

// this * rightMatrix
Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& rightMatrix) const
{
    Matrix4x4 result;

    result.f11 = f11 * rightMatrix.f11 + f12 * rightMatrix.f21 + f13 * rightMatrix.f31 + f14 * rightMatrix.f41;
    result.f12 = f11 * rightMatrix.f12 + f12 * rightMatrix.f22 + f13 * rightMatrix.f32 + f14 * rightMatrix.f42;
    result.f13 = f11 * rightMatrix.f13 + f12 * rightMatrix.f23 + f13 * rightMatrix.f33 + f14 * rightMatrix.f43;
    result.f14 = f11 * rightMatrix.f14 + f12 * rightMatrix.f24 + f13 * rightMatrix.f34 + f14 * rightMatrix.f44;

    result.f21 = f21 * rightMatrix.f11 + f22 * rightMatrix.f21 + f23 * rightMatrix.f31 + f24 * rightMatrix.f41;
    result.f22 = f21 * rightMatrix.f12 + f22 * rightMatrix.f22 + f23 * rightMatrix.f32 + f24 * rightMatrix.f42;
    result.f23 = f21 * rightMatrix.f13 + f22 * rightMatrix.f23 + f23 * rightMatrix.f33 + f24 * rightMatrix.f43;
    result.f24 = f21 * rightMatrix.f14 + f22 * rightMatrix.f24 + f23 * rightMatrix.f34 + f24 * rightMatrix.f44;

    result.f31 = f31 * rightMatrix.f11 + f32 * rightMatrix.f21 + f33 * rightMatrix.f31 + f34 * rightMatrix.f41;
    result.f32 = f31 * rightMatrix.f12 + f32 * rightMatrix.f22 + f33 * rightMatrix.f32 + f34 * rightMatrix.f42;
    result.f33 = f31 * rightMatrix.f13 + f32 * rightMatrix.f23 + f33 * rightMatrix.f33 + f34 * rightMatrix.f43;
    result.f34 = f31 * rightMatrix.f14 + f32 * rightMatrix.f24 + f33 * rightMatrix.f34 + f34 * rightMatrix.f44;

    result.f41 = f41 * rightMatrix.f11 + f42 * rightMatrix.f21 + f43 * rightMatrix.f31 + f44 * rightMatrix.f41;
    result.f42 = f41 * rightMatrix.f12 + f42 * rightMatrix.f22 + f43 * rightMatrix.f32 + f44 * rightMatrix.f42;
    result.f43 = f41 * rightMatrix.f13 + f42 * rightMatrix.f23 + f43 * rightMatrix.f33 + f44 * rightMatrix.f43;
    result.f44 = f41 * rightMatrix.f14 + f42 * rightMatrix.f24 + f43 * rightMatrix.f34 + f44 * rightMatrix.f44;

    return result;
}

// leftVector * this
Vector4 Matrix4x4::MultiplyLeft(const Vector4& leftVector) const
{
    Vector4 result;

    result.x(leftVector.x() * f11 + leftVector.y() * f21 + leftVector.z() * f31 + leftVector.w() * f41);
    result.y(leftVector.x() * f12 + leftVector.y() * f22 + leftVector.z() * f32 + leftVector.w() * f42);
    result.z(leftVector.x() * f13 + leftVector.y() * f23 + leftVector.z() * f33 + leftVector.w() * f43);
    result.w(leftVector.x() * f14 + leftVector.y() * f24 + leftVector.z() * f34 + leftVector.w() * f44);

    return result;
}

// this * rightVector
Vector4 Matrix4x4::MultiplyRight(const Vector4& rightVector) const
{
    Vector4 result;

    result.x(f11 * rightVector.x() + f12 * rightVector.y() + f13 * rightVector.z() + f14 * rightVector.w());
    result.y(f21 * rightVector.x() + f22 * rightVector.y() + f23 * rightVector.z() + f24 * rightVector.w());
    result.z(f31 * rightVector.x() + f32 * rightVector.y() + f33 * rightVector.z() + f34 * rightVector.w());
    result.w(f41 * rightVector.x() + f42 * rightVector.y() + f43 * rightVector.z() + f44 * rightVector.w());

    return result;
}

Matrix4x4 Matrix4x4::GetTranslation(const Vector2& translation)
{
    return Matrix4x4(1.0, 0.0f, 0.0f, translation.x(),
                    0.0f, 1.0f, 0.0f, translation.y(),
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::GetRotationX(const float radians)
{
    return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f, cosf(radians), -sinf(radians), 0.0f,
                    0.0f, sinf(radians), cosf(radians), 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::GetRotationY(const float radians)
{
    return Matrix4x4(cosf(radians), 0, sinf(radians), 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    -sinf(radians), 0.0f, cosf(radians), 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::GetRotationZ(const float radians)
{
    return Matrix4x4(cosf(radians), -sinf(radians), 0.0f, 0.0f,
                    sinf(radians), cosf(radians), 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::GetScale(const float scale)
{
    return Matrix4x4(scale, 0.0f, 0.0f, 0.0f,
                    0.0f, scale, 0.0f, 0.0f,
                    0.0f, 0.0f, scale, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}