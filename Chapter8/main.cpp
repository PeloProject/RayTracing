#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "hitable_list.h"
#include "sphere.h"
#include "float.h"
#include "camera.h"
#include <random>

//***************************************************************************
// �����Z���k�E�c�C�X�^�[�@�ɂ��[��������������A	
// // �n�[�h�E�F�A�������V�[�h�ɂ��ď�����
std::random_device seed_gen;
std::mt19937 engine(seed_gen());

// ��l�������z
// [0.0f, 1.0f)�̒l�͈̔͂ŁA���m���Ɏ����𐶐�����
std::uniform_real_distribution<float> g_rand(0.0f, 1.0f);

float drand48()
{
	return g_rand(engine);
}

vec3 random_vector()
{
	return vec3(drand48(), drand48(), drand48());
}

//�P���Ƀ����_�������ւ̔��˂Ŋg�U�ʂ��ߎ�����
// �i�����o�[�g���˂�p���Ȃ��̂́A����͌�����w�i�i��j�S�̖̂��w���������Ƃ��ċߎ����Ă��邽�߁j�B
// �Փ˓_�ɐڂ���P�ʉ~���a���Ɋ܂܂�郉���_���ȓ_��I�сA
// �Փ˓_���炻����֌������x�N�g�����g�U���˃x�N�g���Ƃ���B
vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		// ���̑S�����ɗ����˂�����
		p = random_vector() * 2.0f - vec3(1.0f,1.0f,1.0f);
		//p = random_vector();
	} while (p.squared_length() >= 1.0f);

	return p;
}

vec3 Color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return Color( ray(rec.p, target-rec.p), world) * 0.5f;
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

			// 1�s�N�Z�����i0.0�`1.0�j�̊Ԃ������_���łP�O�O��Y���V�Ȃ���g���[�X����
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

