#pragma once

#include "material.h"

vec3 reflect(const vec3& v, const vec3& n);

class dielectric : public material
{
public:

	float ref_idx;

	dielectric(float ri) : ref_idx(ri) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{

		attenuation = vec3(1.0f, 1.0f, 1.0f);
		double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

		vec3 unit_direction = UnitVector(r_in.Direction());
		double cos_theta = fmin(Dot(unit_direction * -1.0f, rec.normal), 1.0f);
		double sin_theta = sqrt(1.0f - cos_theta * cos_theta);
		if (etai_over_etat * sin_theta > 1.0f)
		{
			vec3 reflected = reflect(unit_direction, rec.normal);
			scattered = ray(rec.p, reflected);
			return true;
		}
		//double reflect_prob = schlick(cos_theta, etai_over_etat);
		//if (random_double() < reflect_prob)
		//{
		//	vec3 reflected = reflect(unit_direction, rec.normal);
		//	scattered = ray(rec.p, reflected);
		//	return true;
		//}

		vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
		scattered = ray(rec.p, refracted);
		return true;
	}

};

