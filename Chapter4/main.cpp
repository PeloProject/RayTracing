#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"


bool HitSphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.Origin() - center;
	float a = Dot(r.Direction(), r.Direction());
	float b = Dot(oc, r.Direction()) * 2.0f;
	float c = Dot(oc, oc) - radius*radius;
	float discriminant = b * b - 4 * a * c;
	return discriminant > 0;

}

vec3 Color(const ray& r)
{
	if (HitSphere(vec3(0, 0, -1), 0.5f, r))
	{
		return vec3(1, 0, 0);
	}
	vec3 unitDirection = UnitVector(r.Direction());
	float t = 0.5f * (unitDirection.y() + 1.0f);
	return vec3(1.0f, 1.0f, 1.0f) * (1.0f - t) + vec3(0.5f, 0.7f, 1.0f) * t;
}

int main()
{
	int nx = 200;
	int ny = 100;

	// outputfile
	std::ofstream outputfile("image.ppm");

	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outputfile << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lowerLeftCorner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);
	
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);

			ray r(origin, lowerLeftCorner + horizontal * u + vertical * v);
				vec3 color = Color(r);

			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			outputfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputfile.close();
}
