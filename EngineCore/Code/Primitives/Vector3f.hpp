#pragma once
#ifndef include_VECTOR3F
#define include_VECTOR3F

#include <math.h>
#include <string>

class Vector3f
{
public:
	float x;
	float y;
	float z;

	Vector3f()
		:x(0)
		,y(0)
		,z(0)
	{
	}

	Vector3f(float a, float b, float c)
		:x(a)
		,y(b)
		,z(c)
	{
	}

	Vector3f(float d[3])
		:x(d[0])
		,y(d[1])
		,z(d[2])
	{
	}

	Vector3f(std::string initString)
	{
		int currentDimension = 0;
		std::string currentDimensionString = "";
		for(unsigned int ii = 0; ii < initString.size(); ii++)
		{
			std::string currentCharacter = initString.substr(ii, 1);
			if(currentCharacter == " ")
			{
				//do nothing
			}
			else if(currentCharacter == ",")
			{
				switch(currentDimension)
				{
				case 0:
					x = (float) atof(currentDimensionString.c_str());
					break;
				case 1:
					y = (float) atof(currentDimensionString.c_str());
					break;
				case 2:
					z = (float) atof(currentDimensionString.c_str());
				default:
					//TODO: ASSERT
					break;
				}
				currentDimension++;
				currentDimensionString = "";
			}
			else
			{
				currentDimensionString.append(currentCharacter);
			}
			if (currentDimensionString != "")
			{
				y = (float) atof(currentDimensionString.c_str());
			}
		}
	}

	inline Vector3f operator+(const Vector3f& rhs) const
	{
		Vector3f temp = Vector3f();
		temp.x = x + rhs.x;
		temp.y = y + rhs.y;
		temp.z = z + rhs.z;
		return temp;
	}

	inline Vector3f operator-(const Vector3f& rhs) const
	{
		Vector3f temp = Vector3f();
		temp.x = x - rhs.x;
		temp.y = y - rhs.y;
		temp.z = z - rhs.z;
		return temp;
	}

	inline Vector3f operator*(const float& rhs) const
	{
		Vector3f temp = Vector3f();
		temp.x = x * rhs;
		temp.y = y * rhs;
		temp.z = z * rhs;
		return temp;
	}

	inline float magnitude() const
	{
		float magnitude = sqrt(x*x+y*y+z*z);
		return magnitude;
	}

	void normalize()
	{
		float magnitude = sqrt(x*x+y*y+z*z);
		x = x/magnitude;
		y = y/magnitude;
		z = z/magnitude;
	}

	float dot(const Vector3f& rhs) const
	{
		float dotProductValue = 0.f;
		dotProductValue += x * rhs.x;
		dotProductValue += y * rhs.y;
		dotProductValue += z * rhs.z;
		return dotProductValue;
	}

	Vector3f crossProduct(const Vector3f& rhs) const
	{
		Vector3f crossResult = Vector3f();
		crossResult.x = y*rhs.z - z*rhs.y;
		crossResult.y = z*rhs.x - x*rhs.z;
		crossResult.z = x*rhs.y - y*rhs.x;
		return crossResult;
	}

};



#endif