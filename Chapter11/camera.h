#pragma once
#include "ray.h"

class camera
{
public:
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist)
	{
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h;
		auto viewport_width = aspect_ratio * viewport_height;
		auto focal_length = 1.0;

		auto w = UnitVector(lookfrom - lookat);
		u = UnitVector(Cross(vup, w));
		v = Cross(w, u);

		origin = lookfrom;
		horizontal = u * viewport_width * focus_dist;
		std::cout << "ForcusDist" << focus_dist << " " << viewport_width << " " << horizontal.r() << "\n";
		vertical   = v * viewport_height * focus_dist;
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - w * focus_dist;
		lens_radius = aperture / 2;
	}

	ray get_ray(float s, float t)
	{
		vec3 rd = random_in_unit_disk() * lens_radius;
		vec3 offset = u * rd.x() + v * rd.y();
		return ray(origin + offset, lower_left_corner + horizontal * s + vertical * t - origin - offset);
	}

	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u;
	vec3 v;
	double lens_radius;
};

