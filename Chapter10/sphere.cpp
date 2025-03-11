#include "sphere.h"

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	rec.mat_prt = mat_ptr;
	vec3 oc = r.Origin() - center;
	float a = Dot(r.Direction(), r.Direction());	// dot(B,B)
	float b = Dot(oc, r.Direction());				// dot(A-C,B)
	float c = Dot(oc, oc) - radius * radius;		// dot(A-C,A-C) -R*R
	float discriminant = b * b - a * c;				// 2���������̉��̌����̃��[�g�����i�������}�C�i�X�̏ꍇ�͉��Ȃ��ƂȂ�܂��B
	if (0 < discriminant)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a; // �ꎟ�̌W���������̏ꍇ�̉��̌���
		if (t_min < temp && temp < t_max)
		{
			rec.t = temp;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			return true;
		}

		temp = (-b + sqrt(b * b - a * c)) / a; // �ꎟ�̌W���������̏ꍇ�̉��̌���
		if (t_min < temp && temp < t_max)
		{
			rec.t = temp;
			rec.p = r.PointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			return true;
		}
	}
	return false;
}

