#pragma once
#ifndef include_CAMERA
#define include_CAMERA

#include "Primitives/Vector2i.hpp"
#include "Primitives/Vector2f.hpp"
#include "Primitives/Vector3f.hpp"
#include "Data.hpp"

enum CAMERA_MODE {ORTHO, PERSPECTIVE};

class Camera
{
public:
	Camera();

	CAMERA_MODE m_cameraMode;
	float m_aspectRatio;
	float m_fieldOfView;
	float m_nearClip;
	float m_farClip;
	Vector2i m_screenDimensionsInPixels;
	Vector3f m_position;
	Vector3f m_orientationDegrees;
	Vector2f m_cameraSizeInWorldUnits;

	void preRenderStep();
	void postRenderStep();

};


#endif