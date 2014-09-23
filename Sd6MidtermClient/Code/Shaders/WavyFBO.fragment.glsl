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


float tolerance = 1.0;

//Random function from http://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
float rand(vec2 co){
  return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec4 baseColor;
	vec4 texelColor;
	vec4 depthVal = texture2D(u_depthTexture, v_texCoord);
	vec4 texSeed = texture2D(u_diffuseTexture, v_texCoord);
	vec2 texCoordOffset = vec2((rand(texSeed.rg)-.5)*.1, (rand(texSeed.br)-.5)*.1);
	if(depthVal.r < tolerance)
	{
		texelColor = texture2D(u_diffuseTexture, v_texCoord+texCoordOffset);
	}
	else
	{
		texelColor = texture2D(u_diffuseTexture, v_texCoord);
	}
	baseColor = texelColor;
	 
	gl_FragColor = baseColor;
}