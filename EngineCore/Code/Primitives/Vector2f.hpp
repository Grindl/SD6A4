#ifndef included_VECTOR2F
#define included_VECTOR2F
#pragma once

#include <math.h>
#include <string>
;

#ifndef included_Vector2
static const float PI = 3.14159265f;
const float ONE_OVER_SQRT_TWO = 1.f/sqrt(2.f);
const float SQRT_THREE_OVER_TWO = sqrt(3.f)/2.f;
#endif

struct Vector2i;

struct Vector2f
{
public:
	float x;
	float y;

	Vector2f();
	Vector2f(float a, float b);
	Vector2f(float c[2]);
	Vector2f(const std::string& initString);
	Vector2f(const Vector2i& conversion);

	inline Vector2f operator+(const Vector2f &that) const;
	inline Vector2f operator-(const Vector2f &that) const;
	inline Vector2f operator*(const float &that) const;
	inline bool operator==(const Vector2f &that) const;

	inline Vector2f polarToCartesian(float degrees, float radius) const;
	inline float magnitude() const;
	inline float degreesOffset() const;
	inline float distanceSquared(const Vector2f &that) const;
	inline Vector2f normalized() const;
};

inline Vector2f Vector2f::operator + (const Vector2f &that) const
{
	Vector2f temp;
	temp.x = this->x+that.x;
	temp.y = this->y+that.y;
	return temp;
}
inline Vector2f Vector2f::operator - (const Vector2f &that) const
{
	Vector2f temp;
	temp.x = this->x-that.x;
	temp.y = this->y-that.y;
	return temp;
}
inline Vector2f Vector2f::operator * (const float &that) const
{
	Vector2f temp;
	temp.x = this->x*that;
	temp.y = this->y*that;
	return temp;
}

inline bool Vector2f::operator == (const Vector2f &that) const
{
	bool temp = true;
	if(x != that.x)
		temp = false;
	if(y != that.y)
		temp = false;
	return temp;
}

inline Vector2f Vector2f::polarToCartesian(float degrees, float radius) const
{
	Vector2f temp;
	temp.x = cos(degrees*PI/180.f)*radius;
	temp.y = sin(degrees*PI/180.f)*radius;
	return temp;
}

inline float Vector2f::magnitude() const
{
	return sqrt(x*x + y*y);
}
inline float Vector2f::degreesOffset() const
{
	float temp = atan2(y, x)*180.f/PI;

	return temp;
}

inline float Vector2f::distanceSquared(const Vector2f &that) const
{
	Vector2f separationVector = *this - that;
	float distanceSquaredVal = (separationVector.x * separationVector.x) + (separationVector.y * separationVector.y);
	return distanceSquaredVal;
}

inline Vector2f Vector2f::normalized() const
{
	Vector2f normedVector = *this;
	normedVector = normedVector * (1.f / normedVector.magnitude());
	return normedVector;
}

#endif