#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "..\Primitives\VertexData.hpp"
#include "..\Rendering\OpenGLFunctions.hpp"
#include "..\Importer\MaxImporter.hpp"
#include "..\Rendering\Texture.hpp"
#include "DebugMultiPoly.hpp"

#include "Memory Manager/MemoryManager.hpp"

//----------------------------------------------------------------------------------------------
DebugMultiPoly::DebugMultiPoly()
{
	m_origin = Vector3f();
	m_firstColor = Color4f();
	m_timeToLiveSeconds = 0.f;
	m_killNextFrame = false;
	m_shouldBeRemoved = false;
	m_hasTexture = false;
	m_material = Material();
	m_material.m_useVBO = true;
	//m_VBOOffset = 0;
	genVBO();
	//Texture* currTex = new Texture(".\\Data\\cobblestonesDiffuse.png");
	//m_material.m_useVBO = true;
	//m_material.m_useDiffuse = true;
	//m_material.m_useShaderProgram=true;
	////currMat-._useShaderProgram = true;
	//m_material.m_diffuseID = currTex->m_openGLTextureID;
}

//----------------------------------------------------------------------------------------------
DebugMultiPoly::DebugMultiPoly(Vector3f origin, Color4f sideColor, float displayForSeconds, bool depthTest)
{

}

//----------------------------------------------------------------------------------------------
void DebugMultiPoly::render()
{
	if(m_depthTest)
	{
		glEnable(GL_DEPTH_TEST);
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
	}

	for(unsigned int TriFragIterator = 0; TriFragIterator < m_rootTriFragNodes.size(); TriFragIterator++)
	{
		recursiveRender(m_rootTriFragNodes[TriFragIterator]);
	}

}

//----------------------------------------------------------------------------------------------
void DebugMultiPoly::update(float deltaSeconds)
{
	m_timeToLiveSeconds += deltaSeconds;
}

//----------------------------------------------------------------------------------------------
void DebugMultiPoly::genVBO()
{
	//for(unsigned int VBOIterator = 0; VBOIterator < m_triBatchSizeAtlass.size(); VBOIterator++)
	//{
	//	VertexData* m_VBO = MaxImporter::ImportFrom3DSMaxToVertexData(".\\Data\\IYAMATEST.CHUMBA", m_VBOOffset);
	//	glGenBuffers(1, &m_VBOAtlass[VBOIterator]);
	//	glBindBuffer(GL_ARRAY_BUFFER, m_OGLBuffer);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData)*m_VBOOffset, m_VBO, GL_STATIC_DRAW);
	//	delete m_VBO;
	//}
}

//----------------------------------------------------------------------------------------------
void DebugMultiPoly::recursiveRender(TriFragNode* currentNode)
{
	glPushMatrix();

	float maxTime = currentNode->keyframeTime.back();

	float adjustedTime = fmodf(m_timeToLiveSeconds, maxTime);
	if (maxTime == 0.f)
	{
		adjustedTime = 0.f; //corrects for NaN
	}
	bool timeExceeded = false;
	int matrixFrame = -1;
	unsigned int keyframeIndex;
	for (keyframeIndex = 0; keyframeIndex < currentNode->transform.size() && !timeExceeded; keyframeIndex++)
	{
		if (adjustedTime < currentNode->keyframeTime[keyframeIndex])
		{
			timeExceeded = true;
		}
	}

	glMultMatrixf(currentNode->transform[keyframeIndex-1]); //TODO reference the ttl seconds

	if (currentNode->sizeOfVBO > 0)
	{

		//TODO render thyself
		glBindBuffer(GL_ARRAY_BUFFER, currentNode->VBOID);

		//Note to self: this was moved from render() because it needs to be after bind buffer, but render is unsure if a VBO is being used
		currentNode->material->m_primaryLightSource = m_material.m_primaryLightSource;
		currentNode->material->m_lightBufferID = m_material.m_lightBufferID;
		currentNode->material->m_cameraPosition = m_material.m_cameraPosition;
		currentNode->material->m_shaderID = m_material.m_shaderID;
		currentNode->material->m_shaderProgram = m_material.m_shaderProgram;
		currentNode->material->prepareOpenGLForMaterial();
		//m_material.prepareOpenGLForMaterial();

		

		glDrawArrays(GL_TRIANGLES, 0, currentNode->sizeOfVBO);

	}
	glPopMatrix(); 
	for (unsigned int triFragIndex = 0; triFragIndex < currentNode->children.size(); triFragIndex++)
	{
		recursiveRender(currentNode->children[triFragIndex]);
	}
	
}