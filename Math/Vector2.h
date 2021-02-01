#ifndef __VECTOR2_H
#define __VECTOR2_H

namespace Engine
{
namespace Math
{

class Vector2
{
public:
	// standard constructor
	inline Vector2(int i_x, int i_y);
	// copy constructor - for completeness
	inline Vector2(const Vector2 & i_other);
	// assignment operator
	inline Vector2 & operator=(const Vector2 & i_rhs);

	// element accessors
	// - get individual element
	inline int x(void) const;
	inline int y(void) const;
	// - set individual element
	inline void x(int i_x);
	inline void y(int i_y);
	inline void z(int i_z);

	// modifying operators
	inline Vector2 & operator+=(const Vector2 & i_rhs);
	inline Vector2 & operator-=(const Vector2 & i_rhs);

	inline Vector2 & operator*=(const Vector2 & i_other);
	inline Vector2 & operator*=(int i_val);
	inline Vector2 & operator*=(float i_val);

	inline Vector2 & operator/=(const Vector2 & i_other);
	inline Vector2 & operator/=(int i_val);
	inline Vector2 & operator/=(float i_val);

	// negate
	inline Vector2 operator-(void);

	inline Vector2 & Normalize();
	inline Vector2 Normalized() const;

	inline float Length() const;
	inline int LengthSq() const;
	
	// - ( 0.0f, 0.0f, 0.0f )
	static const Vector2 Zero;

private:
	int	m_x, m_y;

} ;

inline Vector2 Normalized(const Vector2 & i_vec);

inline Vector2 operator+(const Vector2 & i_lhs, const Vector2 & i_rhs);
inline Vector2 operator-(const Vector2 & i_lhs, const Vector2 & i_rhs);

inline Vector2 operator*(const Vector2 & i_lhs, int i_rhs);
inline Vector2 operator*(const Vector2 & i_lhs, float i_rhs);

inline Vector2 operator/(const Vector2 & i_lhs, const Vector2 & i_rhs);
inline Vector2 operator/(const Vector2 & i_lhs, int i_rhs);
inline Vector2 operator/(const Vector2 & i_lhs, float i_rhs);

inline bool operator==(const Vector2 & i_lhs, const Vector2 & i_rhs);
inline bool operator!=(const Vector2 & i_lhs, const Vector2 & i_rhs);

inline int dot(const Vector2 & i_lhs, const Vector2 & i_rhs);

} // namespace Math
} // namespace Engine

#include "Vector2-inl.h"
#endif // __VECTOR2_H