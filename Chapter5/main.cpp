#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

// 参考URL	
//https://qiita.com/tsuchinokoman/items/0106cc6bfd5584b66dd9
//https://www.try-it.jp/chapters-1197/sections-1198/lessons-1207/
float HitSphere(const vec3& center, float radius, const ray& r)
{
	// A = ray origin
	// B = ray direction
	// C = sphere center
	vec3 oc = r.Origin() - center;					// A-C
	float a = Dot(r.Direction(), r.Direction());	// dot(B,B)
	float b = Dot(oc, r.Direction()) * 2.0f;		// 2 * dot(A-C,B)
	float c = Dot(oc, oc) - radius * radius;		// dot(A-C,A-C) -R*R
	float discriminant = b * b - 4 * a * c;			// 2次方程式の解の公式のルート部分（ここがマイナスの場合は解なしとなります。
	if (discriminant < 0)
	{
		return -1.0f;
	}
	else
	{
		float t0 = (-b + sqrtf(discriminant)) / (2.0f * a); // 二次方程式の解を求めて、視点から交点までの長さを算出
		float t1 = (-b - sqrtf(discriminant)) / (2.0f * a); // 二次方程式の解を求めて、視点から交点までの長さを算出
		return t1;
	}
}

vec3 Color(const ray& r)
{
	vec3 center = vec3(0, 0, -1);
	float t = HitSphere(center, 0.5f, r);
	if (t > 0.0f)
	{
		vec3 N = UnitVector(r.PointAtParameter(t) - center); // 交点-球の中心で法線ベクトルを求める
		return vec3(N.x() + 1, N.y() + 1, N.z() + 1) * 0.5f;
	}
	vec3 unitDirection = UnitVector(r.Direction());
	t = 0.5f * (unitDirection.y() + 1.0f);
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
