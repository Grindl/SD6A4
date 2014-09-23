#version 110
//
//fragment shader, GLSL 1.10
//
//Inputs:
// screenPosition
//Outputs:
// gl_FragColor - final RGBA color to report to the framebuffer

uniform float u_time;
uniform sampler2D u_diffuseTexture;
uniform float u_useTexture;

varying vec4 v_screenPosition;
varying vec4 v_worldPosition;
varying vec4 v_surfaceColor;
varying vec2 v_texCoord;

float CalcLuminance(vec4 color)
{
	vec3 luminanceCoefficients = vec3(.22, .71, .07);
	float luminance = dot(luminanceCoefficients, color.rgb);
	return luminance;
}

vec4 GetAsGreyscale(vec4 color)
{
	float luminance = CalcLuminance(color);
	return vec4(luminance, luminance, luminance, color.a);
}

vec4 PaintTextureOverColor(vec4 color, vec4 textureColor)
{
	vec4 newColor;
	float blendValue = min(u_useTexture, textureColor.a);
	newColor.r = color.r * (1.0 - blendValue) + textureColor.r * blendValue;
	newColor.g = color.g * (1.0 - blendValue) + textureColor.g * blendValue;
	newColor.b = color.b * (1.0 - blendValue) + textureColor.b * blendValue;
	newColor.a = max(color.a, textureColor.a);
	return newColor;
}

vec4 PulseWithTime(vec4 color)
{
	float adjustedTime = sin(u_time)*.5 + .5;
	vec4 greyscale = GetAsGreyscale(color);
	vec4 newColor;
	newColor.r = color.r * (1.0 - adjustedTime) + greyscale.r * adjustedTime;
	newColor.g = color.g * (1.0 - adjustedTime) + greyscale.g * adjustedTime;
	newColor.b = color.b * (1.0 - adjustedTime) + greyscale.b * adjustedTime;
	newColor.a = color.a;
	return newColor;
}

//TODO two different shaders, one which uses textures and one which does not
vec4 BlendTextureAndColor(vec4 color, vec4 textureColor)
{
	vec4 newColor;
	if(u_useTexture > 0.0)
	{
		newColor = color * textureColor;
	}
	else
	{
		newColor = color;
	}
	return newColor;
}

void main()
{
	vec4 diffuseTexel;
	diffuseTexel = texture2D(u_diffuseTexture, v_texCoord);
	vec4 newColor;
	newColor = BlendTextureAndColor(v_surfaceColor, diffuseTexel);
	if(u_time != 0.0)
	{
		newColor = PulseWithTime(newColor);
	}
	gl_FragColor = newColor;
}

