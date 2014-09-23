#pragma once
#ifndef include_DEBUGMULTIPOLY
#define include_DEBUGMULTIPOLY

#include <vector>

#include "DebugElement.hpp"

class DebugMultiPoly : public DebugElement
{
private:

public:

	struct TriFragNode 
	{
		std::vector<float*> transform;
		std::vector<float> keyframeTime; //synched with transform
		std::vector<TriFragNode*> children;
		int index;
		int materialIndex; //Only used for insertion
		Material* material;
		unsigned int sizeOfVBO;
		unsigned int VBOID;
	};

	DebugMultiPoly();
	DebugMultiPoly(Vector3f origin, Color4f sideColor, float displayForSeconds, bool depthTest);

	std::vector<Material*> m_materialAtlass;
	std::vector<unsigned int> m_triBatchSizeAtlass;
	std::vector<unsigned int> m_VBOAtlass;
	std::vector<float[16]> m_translationAtlass; //might be deprecated soon
	std::vector<TriFragNode*> m_rootTriFragNodes;
	//float m_internalTime;
	//int m_VBOOffset;
	//unsigned int m_OGLBuffer;

	virtual void render();
	virtual void update(float deltaSeconds);
	void genVBO();
	void recursiveRender(TriFragNode* currentNode);

};


#endif