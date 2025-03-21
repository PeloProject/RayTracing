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

vec3 random_vector()
{
    return vec3(drand48(), drand48(), drand48());
}

//単純にランダム方向への反射で拡散面を近似する
// （ランバート反射を用いないのは、今回は光源を背景（空）全体の無指向性光源として近似しているため）。
// 衝突点に接する単位円半径内に含まれるランダムな点を選び、
// 衝突点からそちらへ向かうベクトルを拡散反射ベクトルとする。
vec3 random_in_unit_sphere()
{
    vec3 p;
    do
    {
        // 球体全方向に乱反射させる
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


// シュリックの近似式
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