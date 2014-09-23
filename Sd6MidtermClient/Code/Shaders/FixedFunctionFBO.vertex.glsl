#version 110

// Vertex Shader, GLSL v 3.30
// Designed to replace the fixed fucntion pipeline, supports only diffuse texturing
//
//
//
//

uniform sampler2D u_diffuseTexture;
uniform bool u_useTexture;
uniform sampler2D u_depthTexture;
uniform float u_time;

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;


//varying vec3 v_vertex;
//varying vec4 v_colorIn;
//varying vec2 v_texCoordIn;

varying vec4 v_surfaceColor;
varying vec2 v_texCoord;
//out vec4 gl_Position;
varying vec3 v_worldPosition;



void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//v_screenPosition = gl_Position;
	v_worldPosition = gl_Vertex.xyz;
	v_surfaceColor = gl_Color;
	v_texCoord = gl_MultiTexCoord0.xy;
}
	
	
