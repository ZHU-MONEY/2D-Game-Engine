#pragma once
#include "Vector2.h"

class Vector4
{
public:
	Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
	Vector4(const Vector2& other, float z = 0.0f, float w = 0.0f);
	Vector4(const Vector4& copy);

	~Vector4()
	{}

	// accessors and mutators
	inline float x() const;
	inline void x(float x);
	inline float y() const;
	inline void y(float y);
	inline float z() const;
	inline void z(float z);
	inline float w() const;
	inline void w(float w);
	inline void set(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

	// assignment
	inline Vector4& operator=(const Vector4& other);

	// arithmetic
	inline Vector4 operator+(const Vector4& other) const;
	inline Vector4& operator+=(const Vector4& other);
	inline Vector4 operator-(const Vector4& other) const;
	inline Vector4& operator-=(const Vector4& other);
	inline Vector4 operator*(float scale) const;
	inline Vector4& operator*=(float scale);

	// relational
	inline bool operator==(const Vector4& other) const;
	inline bool operator!=(const Vector4& other) const;

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