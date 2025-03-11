#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "float.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

vec3 Color(const ray& r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_prt->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * Color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
		
	}
	else
	{
		vec3 unit_direction = UnitVector(r.Direction());
		float t = (unit_direction.y() + 1.0f) * 0.5f;
		return vec3(1.0f, 1.0f, 1.0f)*(1.0f - t) + vec3(0.5f, 0.7f, 1.0f) * t;
	}
}


//***************************************************************************

int main()
{
	int nx = 200*1;
	int ny = 100*1;
	int ns = 100;

	// outputfile
	std::ofstream outputfile("image.ppm");

	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outputfile << "P3\n" << nx << " " << ny << "\n255\n";

	camera cam;

	hitable* list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8f, 0.3f,0.3f)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8f, 0.6f, 0.2f), 0.3f));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5f));
	hitable* world = new hitable_list(list, 4);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 color(0.0f, 0.0f, 0.0f);

			// 1ピクセル内（0.0～1.0）の間をランダムで１００回ズラシながらトレースする
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				//std::cout << s << " " << u << " " << v << "\n";
				ray r = cam.get_ray(u, v);
				vec3 p = r.PointAtParameter(2.0f);
				color = color + Color(r, world, 0);
			}

			color = color/(float)ns;
			color = vec3(sqrtf(color[0]), sqrtf(color[1]), sqrtf(color[2]));

			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			outputfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputfile.close();
}

