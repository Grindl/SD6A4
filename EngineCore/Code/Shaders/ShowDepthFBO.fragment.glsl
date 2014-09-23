#version 110

uniform sampler2D u_diffuseTexture;
uniform bool u_useTexture;
uniform sampler2D u_depthTexture;
uniform float u_time;

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;


//out vec4 fragmentColor;

varying vec3 v_worldPosition;
varying vec4 v_surfaceColor;
varying vec2 v_texCoord;



void main()
{
	vec4 baseColor;
	vec4 texColor = texture2D(u_depthTexture, v_texCoord);
	baseColor = v_surfaceColor * texColor;
	gl_FragColor = baseColor;
}