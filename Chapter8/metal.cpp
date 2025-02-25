#include "metal.h"

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - n * Dot(v, n) * 2.0f;
}