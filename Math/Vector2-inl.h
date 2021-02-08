#include <math.h>

namespace Engine
{
namespace Math
{
	
inline Vector2::Vector2(int i_x, int i_y) :
	x_(i_x),
	y_(i_y)
{
}

inline Vector2::Vector2(const Vector2 & i_other) :
	x_(i_other.x_),
	y_(i_other.y_)
{
}

// operators
inline Vector2 & Vector2::operator=(const Vector2 & i_other)
{
	x_ = i_other.x_;
	y_ = i_other.y_;

	return *this;
}

// accessors
inline int Vector2::x(void) const
{
	return x_;
}

inline int Vector2::y(void) const
{
	return y_;
}

inline void Vector2::x(int i_x)
{
	x_ = i_x;
}

inline void Vector2::y(int i_y)
{
	y_ = i_y;
}

inline Vector2 & Vector2::operator+=(const Vector2 & i_other)
{
	x_ += i_other.x_;
	y_ += i_other.y_;

	return *this;
}

inline Vector2 & Vector2::operator-=(const Vector2 & i_other)
{
	x_ -= i_other.x_;
	y_ -= i_other.y_;

	return *this;
}

inline Vector2 & Vector2::operator*=(const Vector2 & i_other)
{
	x_ *= i_other.x_;
	y_ *= i_other.y_;

	return *this;
}

inline Vector2 & Vector2::operator*=(int i_other)
{
	x_ *= i_other;
	y_ *= i_other;

	return *this;
}

inline Vector2 & Vector2::operator*=(float i_other)
{
	x_ *= int(i_other * x_);
	y_ *= int(i_other * y_);

	return *this;
}

inline Vector2 & Vector2::operator/=(const Vector2 & i_other)
{
	x_ /= i_other.x_;
	y_ /= i_other.y_;

	return *this;
}

inline Vector2 & Vector2::operator/=(int i_other)
{
	x_ /= i_other;
	y_ /= i_other;

	return *this;
}

inline Vector2 & Vector2::operator/=(float i_other)
{
	x_ = int( (float) x_ / i_other);
	y_ = int( (float) y_ / i_other);

	return *this;
}

inline Vector2 Vector2::operator-(void)
{
	return Vector2(-x_, -y_);
}

inline int Vector2::LengthSq() const
{
	return (x_ * x_) + (y_ * y_);
}

inline float Vector2::Length() const
{
	return static_cast<float>( sqrt(LengthSq()));
}

inline Vector2 & Vector2::Normalize()
{
	*this = Normalized();

	return *this;
}

// stand alone operators
inline Vector2 operator+( const Vector2 & i_lhs, const Vector2 & i_rhs )
{
	return Vector2( i_lhs.x() + i_rhs.x(), i_lhs.y() + i_rhs.y() );
}

inline Vector2 operator-( const Vector2 & i_lhs, const Vector2 & i_rhs )
{
	return Vector2( i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y() );
}

inline Vector2 operator*( const Vector2 & i_lhs, const Vector2 & i_rhs )
{
	return Vector2( i_lhs.x() * i_rhs.x(), i_lhs.y() * i_rhs.x() );
}

inline Vector2 operator*( const Vector2 & i_lhs, int i_rhs )
{
	return Vector2( i_lhs.x() * i_rhs, i_lhs.y() * i_rhs );
}

inline Vector2 operator*(const Vector2 & i_lhs, float i_rhs)
{
	return Vector2(int( i_rhs * i_lhs.x()), int( i_rhs * i_lhs.y()));
}

inline Vector2 operator*( int i_lhs, const Vector2 & i_rhs )
{
	return Vector2( i_lhs * i_rhs.x(), i_lhs * i_rhs.y() );
}

inline Vector2 operator/( const Vector2 & i_lhs, const Vector2 & i_rhs )
{
	return Vector2( i_lhs.x() / i_rhs.x(), i_lhs.y() / i_rhs.y() );
}

inline Vector2 operator/( const Vector2 & i_lhs, int i_rhs )
{
	return Vector2( i_lhs.x() / i_rhs, i_lhs.y() / i_rhs );
}

inline Vector2 operator/(const Vector2 & i_lhs, float i_rhs)
{
	return Vector2(int( (float) i_lhs.x() / i_rhs), int( (float) i_lhs.y() / i_rhs));
}

inline bool operator==( const Vector2 & i_lhs, const Vector2 & i_rhs )
{
	return (i_lhs.x() == i_rhs.x()) && (i_lhs.y() == i_rhs.y() ); 
}

inline bool operator!=( const Vector2 & i_lhs, const Vector2 & i_rhs )
{
	return !operator==(i_lhs, i_rhs);
}

inline int dot( const Vector2 & i_lhs, const Vector2 & i_rhs )
{
	return i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y();
}

} // namespace Math
} // namespace Engine