#pragma once
#include <cmath>
inline bool RoundedEqual(float left, float right)
{
	return fabs(fabs(right) - fabs(left)) < 0.0001f;
}