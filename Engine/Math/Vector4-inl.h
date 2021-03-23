#pragma once
#include "Vector4.h"
inline float Vector4::x() const
{
	return x_;
}

inline void Vector4::x(float i_x)
{
	x_ = i_x;
}

inline float Vector4::y() const
{
	return y_;
}

inline void Vector4::y(float i_y)
{
	y_ = i_y;
}

inline float Vector4::z() const
{
	return z_;
}

inline void Vector4::z(float i_z)
{
	z_ = i_z;
}

inline float Vector4::w() const
{
	return w_;
}

inline void Vector4::w(float i_w)
{
	w_ = i_w;
}

inline void Vector4::set(float i_x, float i_y, float i_z, float i_w)
{
	x_ = i_x;
	y_ = i_y;
	z_ = i_z;
	w_ = i_w;
}

inline Vector4& Vector4::operator=(const Vector4& i_vec)
{
	// check for self assignment
	if (this != &i_vec)
	{
		x_ = i_vec.x_;
		y_ = i_vec.y_;
		z_ = i_vec.z_;
		w_ = i_vec.w_;
	}

	return *this;
}

inline Vector4 Vector4::operator+(const Vector4& i_vec) const
{
	return Vector4(x_ + i_vec.x(), y_ + i_vec.y(), z_ + i_vec.z(), w_ + i_vec.w());
}

inline Vector4& Vector4::operator+=(const Vector4& i_vec)
{
	x(x_ + i_vec.x());
	y(y_ + i_vec.y());
	z(z_ + i_vec.z());
	w(w_ + i_vec.w());
	return *this;
}

inline Vector4 Vector4::operator-(const Vector4& i_vec) const
{
	return Vector4(x_ - i_vec.x(), y_ - i_vec.y(), z_ - i_vec.z(), w_ - i_vec.w());
}

inline Vector4& Vector4::operator-=(const Vector4& i_vec)
{
	x(x_ - i_vec.x());
	y(y_ - i_vec.y());
	z(z_ - i_vec.z());
	w(w_ - i_vec.w());
	return *this;
}

inline Vector4 Vector4::operator*(float i_scale) const
{
	return Vector4(x_ * i_scale, y_ * i_scale, z_ * i_scale, w_ * i_scale);
}

inline Vector4& Vector4::operator*=(float i_scale)
{
	x(x_ * i_scale);
	y(y_ * i_scale);
	z(z_ * i_scale);
	w(w_ * i_scale);
	return *this;
}

inline bool Vector4::operator==(const Vector4& i_vec) const
{
	return x_== i_vec.x() && y_== i_vec.y() && z_== i_vec.z() && w_== i_vec.w();
}

inline bool Vector4::operator!=(const Vector4& i_vec) const
{
	return (x_ != i_vec.x() || y_ != i_vec.y() || z_ != i_vec.z() || w_ != i_vec.w());
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