#pragma once
#include "Vector4.h"
#include "Engine/Math/MathUtils.h"

inline float Vector4::x() const
{
	return x_;
}

inline void Vector4::x(float x)
{
	x_ = x;
}

inline float Vector4::y() const
{
	return y_;
}

inline void Vector4::y(float y)
{
	y_ = y;
}

inline float Vector4::z() const
{
	return z_;
}

inline void Vector4::z(float z)
{
	z_ = z;
}

inline float Vector4::w() const
{
	return w_;
}

inline void Vector4::w(float w)
{
	w_ = w;
}

inline void Vector4::set(float x, float y, float z, float w)
{
	x_ = x;
	y_ = y;
	z_ = z;
	w_ = w;
}

inline Vector4& Vector4::operator=(const Vector4& other)
{
	// check for self assignment
	if (this != &other)
	{
		x_ = other.x_;
		y_ = other.y_;
		z_ = other.z_;
		w_ = other.w_;
	}

	return *this;
}

inline Vector4 Vector4::operator+(const Vector4& other) const
{
	return Vector4(x_ + other.x(), y_ + other.y(), z_ + other.z(), w_ + other.w());

}

inline Vector4& Vector4::operator+=(const Vector4& other)
{
	x(x_ + other.x());
	y(y_ + other.y());
	z(z_ + other.z());
	w(w_ + other.w());
	return *this;
}

inline Vector4 Vector4::operator-(const Vector4& other) const
{
	return Vector4(x_ - other.x(), y_ - other.y(), z_ - other.z(), w_ - other.w());
}

inline Vector4& Vector4::operator-=(const Vector4& other)
{
	x(x_ - other.x());
	y(y_ - other.y());
	z(z_ - other.z());
	w(w_ - other.w());
	return *this;
}

inline Vector4 Vector4::operator*(float scale) const
{
	return Vector4(x_ * scale, y_ * scale, z_ * scale, w_ * scale);
}

inline Vector4& Vector4::operator*=(float scale)
{
	x(x_ * scale);
	y(y_ * scale);
	z(z_ * scale);
	w(w_ * scale);
	return *this;
}

inline bool Vector4::operator==(const Vector4& other) const
{
	//return x_== other.x() && y_== other.y() && z_== other.z() && w_== other.w();
	return (RoundedEqual(x_, other.x()) && RoundedEqual(y_, other.y()) && RoundedEqual(z_, other.z()) && RoundedEqual(w_, other.w()));
}

inline bool Vector4::operator!=(const Vector4& other) const
{
	return (x_ != other.x() || y_ != other.y() || z_ != other.z() || w_ != other.w());
}

inline Vector4 Vector4::operator-() const
{
	return Vector4(-x(), -y(), -z(), -w());
}

inline bool Vector4::IsZero() const
{
	return x_ == 0.0f && y_ == 0.0f && z_ == 0.0f && w_ == 0.0f;
}

inline bool Vector4::IsOne() const
{
	return x_== 1.0f && y_== 1.0f && z_== 1.0f && w_== 1.0f;
}

inline bool Vector4::IsPoint() const
{
	return !(w_== 0.0f);
}

inline float Vector4::LengthSquared() const
{
	return (x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
}