#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "float.h"
#include "camera.h"
#include <random>

vec3 Color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0f, FLT_MAX, rec))
	{
		return vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1) * 0.5f;
	}
	else
	{
		vec3 unit_direction = UnitVector(r.Direction());
		float t = (unit_direction.y() + 1.0f) * 0.5f;
		return vec3(1.0f, 1.0f, 1.0f)*(1.0f - t) + vec3(0.5f, 0.7f, 1.0f) * t;
	}
}

//***************************************************************************
// メルセンヌ・ツイスター法による擬似乱数生成器を、	
// // ハードウェア乱数をシードにして初期化
std::random_device seed_gen;
std::mt19937 engine(seed_gen());

// 一様実数分布
// [0.0f, 1.0f)の値の範囲で、等確率に実数を生成する
std::uniform_real_distribution<float> g_rand(0.0f, 1.0f);

float drand48()
{
	return g_rand(engine);
}
//***************************************************************************

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 10;

	// outputfile
	std::ofstream outputfile("image.ppm");

	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outputfile << "P3\n" << nx << " " << ny << "\n255\n";

	camera cam;

	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable* world = new hitable_list(list, 2);

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
				color = color + Color(r, world);
			}

			color = color/(float)ns;

			int ir = int(255.99 * color[0]);
			int ig = int(255.99 * color[1]);
			int ib = int(255.99 * color[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			outputfile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outputfile.close();
}

