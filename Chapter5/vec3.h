#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{

public:
	float e[3];
	vec3() : e{0} {}
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+(const vec3& v) const { return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]); }
	inline vec3 operator-(float t) const { return vec3(e[0]-t, e[1]-t, e[2]-t); }
	inline vec3 operator-(const vec3& v) const { return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }
	inline vec3 operator*(const vec3& v) const { return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2] ); }
	inline vec3 operator*(float t) const { return vec3(e[0] * t, e[1] * t, e[2] * t); }
	inline vec3 operator/(float t) const { return vec3(e[0] / t, e[1] / t, e[2] / t); }


	inline vec3& operator+=(const vec3& v);
	inline vec3& operator-=(const vec3& v);
	inline vec3& operator*=(const vec3& v);
	inline vec3& operator/=(const vec3& v);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);


	inline float length() const { return sqrt(squared_length()); }
	inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	inline void make_unit_vector();

};

vec3 UnitVector(vec3 v);
float Dot(const vec3 &v1, const vec3& v2);