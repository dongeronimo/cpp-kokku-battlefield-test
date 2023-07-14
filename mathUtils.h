#pragma once
#ifndef _mathutils_h
#include <cmath>

#define _mathutils_h
inline int ManhattanDistance(int a_i, int a_j, int b_i, int b_j) {
	const int distanceToTarget = std::abs(a_i - b_i) +
		std::abs(a_j - b_j);
	return distanceToTarget;
}
#endif