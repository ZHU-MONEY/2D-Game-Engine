#include "Vector2.h"

#include <cmath>

namespace Engine {
	namespace Math {

		const Vector2 Vector2::ZERO(0.0f, 0.0f);
		const Vector2 Vector2::UNIT(1.0f, 1.0f);
		const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
		const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);

		Vector2::Vector2(float i_x, float i_y) : x_(i_x),
			y_(i_y)
		{}

		Vector2::Vector2(const Vector2& i_copy) : x_(i_copy.x_),
			y_(i_copy.y_)
		{}

		float Vector2::Length() const
		{
			return std::sqrtf(LengthSquared());
		}

		void Vector2::Normalize()
		{
			float length_squared = x_ * x_ + y_ * y_;

			// return if already normalized
			if (length_squared== 1.0f)
			{
				return;
			}

			float length = std::sqrtf(length_squared);
			length = 1.0f / length;

			x_ *= length;
			y_ *= length;
		}

		Vector2 Vector2::Normalize() const
		{
			Vector2 v(*this);
			v.Normalize();
			return v;
		}

	} // namespace math
} // namespace engine