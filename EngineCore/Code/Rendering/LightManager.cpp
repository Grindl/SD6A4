#include "OpenGLFunctions.hpp"


#include "LightManager.hpp"

#include "Memory Manager/MemoryManager.hpp"

LightManager::LightManager()
{
	for (int ii = 0; ii< NUMBER_OF_LIGHTS_SUPPORTED; ii++)
	{
		m_lights[ii] = new Light();
		m_lights[ii]->m_blockOffset = ii*sizeof(CompactLight);
	}
}

void LightManager::updateLightsInOpenGL(unsigned int shaderID)
{
	//glBindBuffer(GL_UNIFORM_BUFFER, m_lightBufferID);
	glUseProgram(shaderID);

	for (int ii = 0; ii < NUMBER_OF_LIGHTS_SUPPORTED; ii++)
	{
		//TODO figure out how uniform blocks work
		//if(m_lights[ii]->m_isDirty)
		{
			//m_lights[ii]->sendLightsToOpenGL(m_lightBufferID);
			m_lights[ii]->m_blockOffset = ii;
			CompactLight lightToSendToCard = CompactLight(*m_lights[ii]);
			//const int ASCII_OFFSET = 48;
			//char shaderText[] = "u_lights[0]";
			//shaderText[9] = ii+ASCII_OFFSET;
			unsigned int lightBufferLoc = glGetUniformLocation(shaderID, "u_lights");
			glUniform1fv(lightBufferLoc+ii*sizeof(CompactLight), SIZEOF_LIGHT, lightToSendToCard.values);
			m_lights[ii]->m_isDirty = false;
		}	
	}
}