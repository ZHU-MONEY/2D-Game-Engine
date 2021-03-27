#include "Vector4.h"
#include <cmath>

const Vector4 Vector4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 Vector4::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);

Vector4::Vector4(float x, float y, float z, float w) : 
x_(x),
y_(y),
z_(z),
w_(w)
{
}

Vector4::Vector4(const Vector2& other, float z, float w) : 
x_(other.x()),
y_(other.y()),
z_(z),
w_(w)
{}

Vector4::Vector4(const Vector4& copy) :
x_(copy.x_),
y_(copy.y_),
z_(copy.z_),
w_(copy.w_)
{}

float Vector4::Length() const
{
	return std::sqrtf(LengthSquared());
}

void Vector4::Normalize()
{
	float length_squared = x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;

	// return if already normalized
	if (length_squared== 1.0f)
	{
		return;
	}

	float length = std::sqrtf(length_squared);
	length = 1.0f / length;

	x_ *= length;
	y_ *= length;
	z_ *= length;
	w_ *= length;
}

Vector4 Vector4::Normalize() const
{
	Vector4 v(*this);
	v.Normalize();
	return v;
}