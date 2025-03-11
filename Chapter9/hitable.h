#pragma once

#include "ray.h"

class material;

struct hit_record
{
	float t;
	vec3 p;
	vec3 normal;
	material* mat_prt;
	bool front_face;

	inline void set_face_normal(const ray& r, const vec3& outward_normal) {
		front_face = Dot(r.Direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : outward_normal*-1.0f;
	}
};

class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

