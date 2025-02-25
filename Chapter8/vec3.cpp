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