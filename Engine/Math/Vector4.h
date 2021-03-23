#pragma once
#include "Vector2.h"

class Vector4
{
public:
	Vector4(float i_x = 0.0f, float i_y = 0.0f, float i_z = 0.0f, float i_w = 0.0f);
	Vector4(const Vector2& i_vec2, float i_z = 0.0f, float i_w = 0.0f);
	Vector4(const Vector4& i_copy);

	~Vector4()
	{}

	// accessors and mutators
	inline float x() const;
	inline void x(float i_x);
	inline float y() const;
	inline void y(float i_y);
	inline float z() const;
	inline void z(float i_z);
	inline float w() const;
	inline void w(float i_w);
	inline void set(float i_x = 0.0f, float i_y = 0.0f, float i_z = 0.0f, float i_w = 0.0f);

	// assignment
	inline Vector4& operator=(const Vector4& i_vec);

	// arithmetic
	inline Vector4 operator+(const Vector4& i_vec) const;
	inline Vector4& operator+=(const Vector4& i_vec);
	inline Vector4 operator-(const Vector4& i_vec) const;
	inline Vector4& operator-=(const Vector4& i_vec);
	inline Vector4 operator*(float i_scale) const;
	inline Vector4& operator*=(float i_scale);

	// relational
	inline bool operator==(const Vector4& i_vec) const;
	inline bool operator!=(const Vector4& i_vec) const;

	// unary
	inline Vector4 operator-() const;

	// functions
	inline bool IsZero() const;
	inline bool IsOne() const;
	inline bool IsPoint() const;
	inline float LengthSquared() const;
	float Length() const;
	void Normalize();
	Vector4 Normalize() const;

	// constants
	static const Vector4 ZERO;
	static const Vector4 UNIT;
	static const Vector4 UNIT_X;
	static const Vector4 UNIT_Y;
	static const Vector4 UNIT_Z;
	static const Vector4 UNIT_W;

protected:
	float x_;
	float y_;
	float z_;
	float w_;
};

#include "Vector4-inl.h"