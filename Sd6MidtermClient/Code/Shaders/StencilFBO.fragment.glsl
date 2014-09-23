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

float widthToCheck = 0.005;
float tolerance = 0.01;

void main()
{
	vec4 baseColor;
	vec4 texColor = texture2D(u_depthTexture, v_texCoord);
	vec4 upNeighbor = texture2D(u_depthTexture, v_texCoord + vec2(widthToCheck, 0.0));
	vec4 downNeighbor = texture2D(u_depthTexture, v_texCoord + vec2(-1.0*widthToCheck, 0.0));
	vec4 leftNeighbor = texture2D(u_depthTexture, v_texCoord + vec2(0.0, -1.0*widthToCheck));
	vec4 rightNeighbor = texture2D(u_depthTexture, v_texCoord + vec2(0.0, widthToCheck));

	bool shouldDrawLine = false;
	if(abs(texColor.r - upNeighbor.r) > tolerance)
	{
		shouldDrawLine = true;
	} 
	if(abs(texColor.r - downNeighbor.r) > tolerance)
	{
		shouldDrawLine = true;
	} 
	if(abs(texColor.r - leftNeighbor.r) > tolerance)
	{
		shouldDrawLine = true;
	} 
	if(abs(texColor.r - rightNeighbor.r) > tolerance)
	{
		shouldDrawLine = true;
	}
	
	if(shouldDrawLine)
	{
		baseColor = vec4(0,0,0,1); 
	}
	else
	{
		baseColor = vec4(1,1,1,1);
	}
	 
	gl_FragColor = baseColor;
}