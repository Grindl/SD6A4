#pragma once
#ifndef include_MATERIAL
#define include_MATERIAL

#include "..\Primitives\Vector3f.hpp"
#include "Shader.hpp"

class Material
{
public:
	Material();
	
	enum TEXTURETYPE{DIFFUSE, NORMAL, SPECULAR, EMISSIVE};

	int m_diffuseID;
	int m_normalID;
	int m_specularID;
	//int m_depthmapID;
	int m_emissiveID;
	int m_shaderID;
	Shader m_shaderProgram;
	

	bool m_useDiffuse;
	bool m_useNormal;
	bool m_useSpecular;
	bool m_useDepthMap;
	bool m_useEmissive;
	bool m_useShaderProgram;
	bool m_useVBO;
	bool m_useBones;

	//float modelViewMatrix[16]
	Vector3f m_primaryLightSource;
	unsigned int m_lightBufferID;
	Vector3f m_cameraPosition;

	//TODO find a better name for this function
	void prepareOpenGLForMaterial();
};


#endif