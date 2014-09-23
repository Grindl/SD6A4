#pragma once
#ifndef include_SHADER
#define include_SHADER


#include "OpenGLFunctions.hpp"

#include <string>
#include <map>

class Shader
{
public:
	Shader();
	Shader(const std::string& vertexShaderFileName, const std::string& fragmentShaderFileName);

	static std::map<std::string, int> s_ActiveShaders;

	int m_shaderID;
	std::string m_fragmentFile;
	std::string m_vertexFile;

	int m_diffuseIDLocation;
	int m_normalIDLocation;
	int m_specularIDLocation;
	//int m_depthmapIDLocation;
	int m_emissiveIDLocation;
	int m_shaderIDLocation;

	int m_useDiffuseLocation;
	int m_useNormalLocation;
	int m_useSpecularLocation;
	int m_useDepthMapLocation;
	int m_useEmissiveLocation;

	bool setDiffuseID(const int textureID);
	bool setNormalID(const int textureID);
	bool setSpecularID(const int textureID);
	//bool setDepthmapID(const int textureID);
	bool setEmissiveID(const int textureID);
	bool setShaderID(const int textureID);

	bool setUseDiffuse(const bool usage);
	bool setUseNormal(const bool usage);
	bool setUseSpecular(const bool usage);
	bool setUseDepthMap(const bool usage);
	bool setUseEmissive(const bool usage);

	bool setValueAtLocation(const int value, const int location);
	bool setValueAtLocation(const bool value, const int location);

	int compileShaderPart(const std::string& fileName, int typeOfShader);

};

#endif