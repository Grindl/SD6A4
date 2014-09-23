#pragma once
#ifndef include_BONEVERTEXDATA
#define include_BONEVERTEXDATA

#include "Vector3f.hpp"
#include "Vector2f.hpp"
#include "Color4f.hpp"

struct BoneVertexData
{
public:
	//0 1 2 position XYZ
	//3 4 5 6 RGBA
	//7 8 texture UV
	//9 10 11 Tangent XYZ
	//12 13 14 Bitangent XYZ
	//15 16 17 Normal XYZ
	//18 19 20 21 22 Bone1 ID, Weight, XYZ offset
	//23 24 25 26 27 Bone2 ID, Weight, XYZ offset
	//28 29 30 31 32 Bone3 ID, Weight, XYZ offset
	//33 34 35 36 37 Bone4 ID, Weight, XYZ offset
	float renderData[38]; 

	Vector3f getPosition(){return Vector3f(renderData[0], renderData[1], renderData[2]);}
	Color4f getColor(){return Color4f(renderData[3], renderData[4], renderData[5], renderData[6]);}
	Vector2f getTextureCoord(){return Vector2f(renderData[7], renderData[8]);}
	Vector3f getTangent(){return Vector3f(renderData[9], renderData[10], renderData[11]);}
	Vector3f getBiangent(){return Vector3f(renderData[12], renderData[13], renderData[14]);}
	Vector3f getNormal(){return Vector3f(renderData[15], renderData[16], renderData[17]);}

	void setPosition(Vector3f position)
	{
		renderData[0] = position.x;
		renderData[1] = position.y;
		renderData[2] = position.x;
	}

	void setColor(Color4f color)
	{
		renderData[3] = color.red;
		renderData[4] = color.green;
		renderData[5] = color.blue;
		renderData[6] = color.alphaValue;
	}

	void setTextureCoord(Vector2f textureCoord)
	{
		renderData[7] = textureCoord.x;
		renderData[8] = textureCoord.y;
	}

	void setTangent(Vector3f tangent)
	{
		renderData[9] = tangent.x;
		renderData[10] = tangent.y;
		renderData[11] = tangent.x;
	}

	void setBitangent(Vector3f bitangent)
	{
		renderData[12] = bitangent.x;
		renderData[13] = bitangent.y;
		renderData[14] = bitangent.x;
	}

	void setNormal(Vector3f normal)
	{
		renderData[15] = normal.x;
		renderData[16] = normal.y;
		renderData[17] = normal.x;
	}

	//void setBoneData()
};

#endif