#include "Vector4.h"
#include <cmath>

const Vector4 Vector4::ZERO(0.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4 Vector4::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);

Vector4::Vector4(float i_x, float i_y, float i_z, float i_w) : 
x_(i_x),
y_(i_y),
z_(i_z),
w_(i_w)
{
}

Vector4::Vector4(const Vector2& i_vec2, float i_z, float i_w) : 
x_(i_vec2.x()),
y_(i_vec2.y()),
z_(i_z),
w_(i_w)
{}

Vector4::Vector4(const Vector4& i_copy) :
x_(i_copy.x_),
y_(i_copy.y_),
z_(i_copy.z_),
w_(i_copy.w_)
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