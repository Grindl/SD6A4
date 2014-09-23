#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "OpenGLFunctions.hpp"

#include "..\Primitives\Vector2f.hpp"
#include "..\Primitives\Vector3f.hpp"
#include "..\Primitives\Color4f.hpp"
#include "..\Primitives\VertexData.hpp"
#include "Material.hpp"

#include "Memory Manager/MemoryManager.hpp"

const char* FragmentShader = ".\\Code\\Shaders\\FixedFunction.fragment.glsl";
const char* VertexShader = ".\\Code\\Shaders\\FixedFunction.vertex.glsl";


//TODO this should accept arguments for the shader programs
Material::Material()
{
	initOpenGLFunctions();

	m_useDiffuse = false;
	m_useNormal = false;
	m_useSpecular = false;
	m_useDepthMap = false;
	m_useEmissive = false;
	m_useShaderProgram = true;
	m_useVBO = false;
	m_lightBufferID = 0;

	m_shaderProgram = Shader(VertexShader, FragmentShader);
	m_shaderID = m_shaderProgram.m_shaderID;
	glUseProgram(m_shaderID);
}



void Material::prepareOpenGLForMaterial()
{
	if(m_useShaderProgram)
	{
		glUseProgram(m_shaderID);

		//unsigned int lightBufferLoc = glGetUniformBlockIndex(m_shaderID, "LightBlock");
		//glUniformBlockBinding(m_shaderID, lightBufferLoc, m_lightBufferID);
		//unsigned int lightBufferLoc = glGetUniformLocation(m_shaderID, "u_lights");
		//glUniform1fv(lightBufferLoc+lightBufferOffset, sizeof(CompactLight)/sizeof(float), lightVals);
		int shaderTime = glGetUniformLocation(m_shaderID, "u_time");
		glUniform1f(shaderTime, ((float)rand())/RAND_MAX);

		int cameraPositionLocation = glGetUniformLocation(m_shaderID, "u_cameraPositionWorldSpace");
		glUniform3f(cameraPositionLocation, m_cameraPosition.x, m_cameraPosition.y, m_cameraPosition.z);
		//uniform vec3 u_cameraDirectionVector;


		int diffuseLocation = glGetUniformLocation(m_shaderID, "u_diffuseTexture");
		glUniform1i(diffuseLocation, DIFFUSE);
		if(m_useDiffuse)
		{
			glActiveTexture(GL_TEXTURE0+DIFFUSE);
			glBindTexture(GL_TEXTURE_2D, m_diffuseID);
		}
		int textureFlag = glGetUniformLocation(m_shaderID, "u_useTexture");
		glUniform1f(textureFlag, m_useDiffuse);


		int normalLocation = glGetUniformLocation(m_shaderID, "u_normalTexture");
		glUniform1i(normalLocation, NORMAL); 
		if(m_useNormal)
		{
			glActiveTexture(GL_TEXTURE0+NORMAL);
			glBindTexture(GL_TEXTURE_2D, m_normalID);
			int lightLocation = glGetUniformLocation(m_shaderID, "u_lightVector");
			glUniform3f(lightLocation, m_primaryLightSource.x, m_primaryLightSource.y, m_primaryLightSource.z);
		}
		int normalFlag = glGetUniformLocation(m_shaderID, "u_useNormal");
		glUniform1f(normalFlag, m_useNormal);


		//TODO differentiate between specular map and specular lighting generally
		int specularLocation = glGetUniformLocation(m_shaderID, "u_specularTexture");
		glUniform1i(specularLocation, SPECULAR);
		if(m_useSpecular)
		{
			glActiveTexture(GL_TEXTURE0+SPECULAR);
			glBindTexture(GL_TEXTURE_2D, m_specularID);
			int lightLocation = glGetUniformLocation(m_shaderID, "u_lightVector");
			glUniform3f(lightLocation, m_primaryLightSource.x, m_primaryLightSource.y, m_primaryLightSource.z);
		}

		int specularLightingFlag = glGetUniformLocation(m_shaderID, "u_showSpecular");
		glUniform1f(specularLightingFlag, m_useSpecular);

		int specularMapFlag = glGetUniformLocation(m_shaderID, "u_useSpecular");
		glUniform1f(specularMapFlag, m_useSpecular);


		int emissiveLocation = glGetUniformLocation(m_shaderID, "u_emissiveTexture");
		glUniform1i(emissiveLocation, EMISSIVE);
		if(m_useEmissive)
		{
			glActiveTexture(GL_TEXTURE0+EMISSIVE);
			glBindTexture(GL_TEXTURE_2D, m_emissiveID);
		}
		int emissiveFlag = glGetUniformLocation(m_shaderID, "u_useEmissive");
		glUniform1f(emissiveFlag, m_useEmissive);

		//setting vertex attributes via the VertexData struct

		unsigned int vertexLocation = glGetAttribLocation(m_shaderID, "v_vertex");
		glEnableVertexAttribArray(vertexLocation);
		glBindAttribLocation(m_shaderID, vertexLocation, "v_vertex");
		glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, false, sizeof(VertexData), (float*)0);

		unsigned int colorLocation = glGetAttribLocation(m_shaderID, "v_colorIn");
		glEnableVertexAttribArray(colorLocation);
		glBindAttribLocation(m_shaderID, colorLocation, "v_colorIn");
		glVertexAttribPointer(colorLocation, 4, GL_FLOAT, false, sizeof(VertexData), (float*)(sizeof(Vector3f)));

		unsigned int textureLocation = glGetAttribLocation(m_shaderID, "v_texCoordIn");
		glEnableVertexAttribArray(textureLocation);
		glBindAttribLocation(m_shaderID, textureLocation, "v_texCoordIn");
		glVertexAttribPointer(textureLocation, 2, GL_FLOAT, false, sizeof(VertexData), (float*)(sizeof(Color4f)+sizeof(Vector3f)));

		unsigned int tangentLocation = glGetAttribLocation(m_shaderID, "v_tangentIn");
		glEnableVertexAttribArray(tangentLocation);
		glBindAttribLocation(m_shaderID, tangentLocation, "v_tangentIn");
		glVertexAttribPointer(tangentLocation, 3, GL_FLOAT, false, sizeof(VertexData), (float*)(sizeof(Vector2f)+sizeof(Color4f)+sizeof(Vector3f)));

		unsigned int bitangentLocation = glGetAttribLocation(m_shaderID, "v_bitangentIn");
		glEnableVertexAttribArray(bitangentLocation);
		glBindAttribLocation(m_shaderID, bitangentLocation, "v_bitangentIn");
		glVertexAttribPointer(bitangentLocation, 3, GL_FLOAT, false, sizeof(VertexData), (float*)(sizeof(Vector3f)+sizeof(Vector2f)+sizeof(Color4f)+sizeof(Vector3f)));

		unsigned int normalVectorLocation = glGetAttribLocation(m_shaderID, "v_normalIn");
		glEnableVertexAttribArray(normalVectorLocation);
		glBindAttribLocation(m_shaderID, normalVectorLocation, "v_normalIn");
		glVertexAttribPointer(normalVectorLocation, 3, GL_FLOAT, false, sizeof(VertexData), (float*)(sizeof(Vector3f)+sizeof(Vector3f)+sizeof(Vector2f)+sizeof(Color4f)+sizeof(Vector3f)));

		//TODO: move the matrix calculations in to their own matrix class

		float projectionMatrixVal[16];
		glGetFloatv(GL_PROJECTION_MATRIX, projectionMatrixVal);
		unsigned int projectionMatrixLocation = glGetUniformLocation(m_shaderID, "u_projectionMatrix");
		glUniformMatrix4fv(projectionMatrixLocation, 1, false, projectionMatrixVal);

		float modelViewVal[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, modelViewVal);
		unsigned int modelViewLocation = glGetUniformLocation(m_shaderID, "u_modelViewMatrix");
		glUniformMatrix4fv(modelViewLocation, 1, false, modelViewVal);
	}
	else if(m_useVBO)
	{
		glUseProgram(0);

		glActiveTexture(GL_TEXTURE1);
		glDisable(GL_TEXTURE_2D);

		if(m_useDiffuse)
		{
			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);	
			glBindTexture(GL_TEXTURE_2D, m_diffuseID);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);
		}

		//glActiveTexture(GL_TEXTURE1);
		//glDisable(GL_TEXTURE_2D);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnable(GL_TEXTURE_2D);
		//reminder: this needs to be done by the object containing the vbo
		//glBindBuffer(GL_ARRAY_BUFFER, m_OGLBuffer);
		glBindTexture(GL_TEXTURE_2D, m_diffuseID);
		glVertexPointer(3, GL_FLOAT, sizeof(VertexData), (float*)(0));
		glColorPointer(4, GL_FLOAT, sizeof(VertexData), (float*)(sizeof(Vector3f)));
		glTexCoordPointer(2, GL_FLOAT, sizeof(VertexData), (float*)(sizeof(Color4f)+sizeof(Vector3f)));

	}
	else
	{
		glUseProgram(0);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glActiveTexture(GL_TEXTURE1);
		glDisable(GL_TEXTURE_2D);

		if(m_useDiffuse)
		{
			glActiveTexture(GL_TEXTURE0);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, m_diffuseID);
		}
		else
		{
			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);
		}
	}
}