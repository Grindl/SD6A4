#version 110
//
//vertex shader, GLSL 1.10
//Inputs
// gl_Vertex
// gl_ModelViewProjectionMatrix
//Outputs
// gl_Position
// screenPosition


uniform float u_time;
uniform sampler2D u_diffuseTexture;
uniform float u_useTexture;

varying vec4 v_screenPosition;
varying vec4 v_worldPosition;
varying vec4 v_surfaceColor;
varying vec2 v_texCoord;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	v_screenPosition = gl_Position;
	v_worldPosition = gl_Vertex;
	v_surfaceColor = gl_Color;
	v_texCoord = gl_MultiTexCoord0.xy;
}
