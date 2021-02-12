#ifndef __VECTOR2_H
#define __VECTOR2_H

namespace Engine {
namespace Math {
		class Vector2
		{
		public:
			Vector2(float i_x = 0.0f, float i_y = 0.0f);
			Vector2(const Vector2& i_copy);

			~Vector2()
			{}

			// accessors and mutators
			inline float x() const;
			inline void x(float i_x);
			inline float y() const;
			inline void y(float i_y);
			inline void set(float i_x = 0.0f, float i_y = 0.0f);

			// assignment
			inline Vector2& operator=(const Vector2& i_vec);

			// arithmetic
			inline Vector2 operator+(const Vector2& i_vec) const;
			inline Vector2& operator+=(const Vector2& i_vec);
			inline Vector2 operator-(const Vector2& i_vec) const;
			inline Vector2& operator-=(const Vector2& i_vec);
			inline Vector2 operator*(float i_scale) const;
			inline Vector2& operator*=(float i_scale);

			// relational
			inline bool operator==(const Vector2& i_vec) const;
			inline bool operator!=(const Vector2& i_vec) const;

			// unary
			inline Vector2 operator-() const;

			// functions
			inline bool IsZero() const;
			inline bool IsOne() const;
			inline float LengthSquared() const;
			float Length() const;
			void Normalize();
			Vector2 Normalize() const;

			// constants
			static const Vector2 ZERO;
			static const Vector2 UNIT;
			static const Vector2 UNIT_X;
			static const Vector2 UNIT_Y;

		protected:
			float x_;
			float y_;
		}; // class Vector2

} // namespace math
} // namespace engine

#include "Vector2-inl.h"

#endif