#pragma once
#include <cmath>
inline bool RoundedEqual(float left, float right)
{
	return fabs(fabs(right) - fabs(left)) < 0.0001f;
}

inline float GetMinOfFour(float first, float second, float third, float fourth)
{
    float first_two = first < second ? first : second;
    float last_two = third < fourth ? third : fourth;
    return first_two < last_two ? first_two : last_two;
}

inline float GetMaxOfFour(float first, float second, float third, float fourth)
{
    float first_two = first > second ? first : second;
    float last_two = third > fourth ? third : fourth;
    return first_two > last_two ? first_two : last_two;
}