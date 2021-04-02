#pragma once
#include "Vector2.h"
struct AABB
{
	
	Vector2 center;
	Vector2 extents;
	static const AABB ZERO;
};