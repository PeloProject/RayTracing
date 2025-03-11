#pragma once
#include "ray.h"

class camera
{
public:
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect_ratio)
	{
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h;
		auto viewport_width = aspect_ratio * viewport_height;
		auto focal_length = 1.0;

		auto w = UnitVector(lookfrom - lookat);
		auto u = UnitVector(Cross(vup, w));
		auto v = Cross(w, u);

		origin = lookfrom;
		horizontal = u*viewport_width;
		vertical = v*viewport_height;
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - w;
	}

	ray get_ray(float u, float v) { return ray(origin, lower_left_corner + horizontal * u + vertical * v - origin); }

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

