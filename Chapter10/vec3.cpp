#include "vec3.h"


inline vec3& vec3::operator+=(const vec3& v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline vec3& vec3::operator-=(const vec3& v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const vec3& v)
{
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    e[2] *= v.e[2];
    return *this;
}

inline vec3& vec3::operator/=(const vec3& v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    e[2] /= v.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

inline vec3& vec3::operator/=(const float t)
{
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

inline void vec3::make_unit_vector()
{
    float k = 1.0f / length();
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

vec3 UnitVector(vec3 v)
{
    return v / v.length();
}

float Dot(const vec3& v1, const vec3& v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

vec3 Cross(const vec3& v1, const vec3& v2)
{
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
        v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
        v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

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
        p = random_vector() * 2.0f - vec3(1.0f, 1.0f, 1.0f);
        //p = random_vector();
    } while (p.squared_length() >= 1.0f);

    return p;
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
    vec3 uv = UnitVector(v);

    float dt = Dot(uv, n);
    float discriminant = 1.0f - ni_over_nt * ni_over_nt * (1.0f - dt * dt);
    if (discriminant > 0)
    {
        refracted = (uv - n * dt) * ni_over_nt - n * sqrtf(discriminant);
        return true;
    }
    else
    {
        return false;
    }
}
vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
{
    auto cos_theta = std::fmin(Dot(uv * -1.0f, n), 1.0f);
    vec3 r_out_prep = (uv + n * cos_theta) * etai_over_etat;
    vec3 r_out_parallel = n*-sqrt(std::fabs(1.0 - r_out_prep.squared_length()));
    return r_out_prep + r_out_parallel;
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - n * Dot(v, n) * 2.0f;
}


// �V�����b�N�̋ߎ���
double schlick(double cosine, double ref_idx)
{
	double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
}

double random_double()
{
    // Returns a random real in [0,1).
    return std::rand() / (RAND_MAX + 1.0);
}

double random_double(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;
double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}