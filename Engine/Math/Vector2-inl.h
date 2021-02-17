#include <math.h>
#include "Vector2.h"


		inline float Vector2::x() const
		{
			return x_;
		}

		inline void Vector2::x(float i_x)
		{
			x_ = i_x;
		}

		inline float Vector2::y() const
		{
			return y_;
		}

		inline void Vector2::y(float i_y)
		{
			y_ = i_y;
		}

		inline void Vector2::set(float i_x, float i_y)
		{
			x_ = i_x;
			y_ = i_y;
		}

		inline Vector2& Vector2::operator=(const Vector2& i_vec)
		{
			// check for self assignment
			if (this != &i_vec)
			{
				x_ = i_vec.x_;
				y_ = i_vec.y_;
			}

			return *this;
		}

		inline Vector2 Vector2::operator+(const Vector2& i_vec) const
		{
			return Vector2(x_ + i_vec.x(), y_ + i_vec.y());
		}

		inline Vector2& Vector2::operator+=(const Vector2& i_vec)
		{
			x(x_ + i_vec.x());
			y(y_ + i_vec.y());
			return *this;
		}

		inline Vector2 Vector2::operator-(const Vector2& i_vec) const
		{
			return Vector2(x_ - i_vec.x(), y_ - i_vec.y());
		}

		inline Vector2& Vector2::operator-=(const Vector2& i_vec)
		{
			x(x_ - i_vec.x());
			y(y_ - i_vec.y());
			return *this;
		}

		inline Vector2 Vector2::operator*(float i_scale)
		{
			return Vector2(x_* i_scale, y_ * i_scale);
		}

		inline Vector2& Vector2::operator*=(float i_scale)
		{
			x(x_ * i_scale);
			y(y_ * i_scale);
			return *this;
		}


		inline Vector2 Vector2::operator*(const Vector2& i_vec)
		{
			return Vector2(x_ * i_vec.x(), y_ * i_vec.y());
		}


		inline bool Vector2::operator==(const Vector2& i_vec) const
		{
			return (x_ == i_vec.x()) && (y_ == i_vec.y());
		}

		inline bool Vector2::operator!=(const Vector2& i_vec) const
		{
			return (x_ != i_vec.x() || y_ != i_vec.y());
		}

		inline Vector2 Vector2::operator-() const
		{
			return Vector2(-x(), -y());
		}

		inline bool Vector2::IsZero() const
		{
			return (x_ == 0.0f) && (y_ == 0.0f);
		}

		inline bool Vector2::IsOne() const
		{
			return (x_ == 1.0f) && (y_ == 1.0f);
		}

		inline float Vector2::LengthSquared() const
		{
			return (x_ * x_ + y_ * y_);
		}
