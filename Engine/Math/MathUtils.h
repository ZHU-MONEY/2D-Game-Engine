#pragma once
#include <cmath>
inline bool RoundedEqual(float left, float right)
{
	return fabs(fabs(right) - fabs(left)) < 0.0001f;
}

inline float GetMinOfFour(float i_first, float i_second, float i_third, float i_fourth)
{
    float first_two = i_first < i_second ? i_first : i_second;
    float last_two = i_third < i_fourth ? i_third : i_fourth;
    return first_two < last_two ? first_two : last_two;
}

inline float GetMaxOfFour(float i_first, float i_second, float i_third, float i_fourth)
{
    float first_two = i_first > i_second ? i_first : i_second;
    float last_two = i_third > i_fourth ? i_third : i_fourth;
    return first_two > last_two ? first_two : last_two;
}