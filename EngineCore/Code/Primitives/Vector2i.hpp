#ifndef included_Vector2
#define included_Vector2
#pragma once

#include <math.h>
#include <string>


#ifndef included_VECTOR2F
static const float PI = 3.14159265f;
const float ONE_OVER_SQRT_TWO = 1.f/sqrt(2.f);
const float SQRT_THREE_OVER_TWO = sqrt(3.f)/2.f;
#endif

struct Vector2f;

struct Vector2i
{
public:
	int x;
	int y;

	Vector2i();
	Vector2i(int a, int b);
	Vector2i(int c[2]);
	Vector2i(const std::string& initString);
	Vector2i(const Vector2f& conversion);

	inline Vector2i operator + (const Vector2i &that) const;
	inline Vector2i operator - (const Vector2i &that) const;
	inline Vector2i operator * (const int &that) const;
	inline bool operator == (const Vector2i &that) const;

	static inline Vector2i polarToCartesian(float degrees, float radius);
	inline float magnitude() const;
	inline float degreesOffset() const;
	inline int distanceSquared(const Vector2i &that) const;
	inline int manhattanDistance(const Vector2i &that) const;

};

static const int NUM_VEC_CARDINAL_DIRECTIONS = 4;
static const Vector2i CARDINAL_DIRECTIONS[] = {Vector2i(0,1), Vector2i(1,0), Vector2i(0,-1), Vector2i(-1,0)};

inline Vector2i Vector2i::operator + (const Vector2i &that) const
{
	Vector2i temp;
	temp.x = this->x+that.x;
	temp.y = this->y+that.y;
	return temp;
}

inline Vector2i Vector2i::operator - (const Vector2i &that) const
{
	Vector2i temp;
	temp.x = this->x-that.x;
	temp.y = this->y-that.y;
	return temp;
}

inline Vector2i Vector2i::operator * (const int &that) const
{
	Vector2i temp;
	temp.x = this->x*that;
	temp.y = this->y*that;
	return temp;
}

inline bool Vector2i::operator == (const Vector2i &that) const
{
	bool temp = true;
	if(x != that.x)
		temp = false;
	if(y != that.y)
		temp = false;
	return temp;
}

inline Vector2i Vector2i::polarToCartesian(float degrees, float radius)
{
	Vector2i temp;
	temp.x = (int)(cos(degrees*PI/180.f)*radius);
	temp.y = (int)(sin(degrees*PI/180.f)*radius);
	return temp;
}

inline float Vector2i::magnitude() const
{
	return sqrt((float)(x*x + y*y));
}

inline float Vector2i::degreesOffset() const
{
	float temp = atan2((float)y, (float)x)*180.f/PI;

	return temp;
}


inline int Vector2i::distanceSquared(const Vector2i &that) const
{
	Vector2i separationVector = *this - that;
	int distanceSquaredVal = (separationVector.x * separationVector.x) + (separationVector.y * separationVector.y);
	return distanceSquaredVal;
}

inline int Vector2i::manhattanDistance(const Vector2i &that) const
{
	Vector2i displacement = *this - that;
	int manhattan = abs(displacement.x) + abs(displacement.y);
	return manhattan;
}

#endif