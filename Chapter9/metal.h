#pragma once
#include "material.h"

vec3 reflect(const vec3& v, const vec3& n);

class metal : public material
{
public:
	metal(const vec3& a, float f) : albedo(a)
	{
		if (f < 1)
		{
			fuzz = f;
		}
		else
		{
			fuzz = 1;
		}
	}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 reflected = reflect(UnitVector(r_in.Direction()), rec.normal);
		scattered = ray(rec.p, reflected + random_in_unit_sphere()*fuzz);
		attenuation = albedo;
		return (Dot(scattered.Direction(), rec.normal) > 0);
	}
	vec3 albedo;
	float fuzz;
};

