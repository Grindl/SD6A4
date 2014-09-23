#version 110
//
//fragment shader, GLSL 1.10
//
//Inputs:
// screenPosition
//Outputs:
// gl_FragColor - final RGBA color to report to the framebuffer

uniform sampler2D u_diffuseTexture;
uniform float u_useTexture;

varying vec4 v_screenPosition;
varying vec4 v_worldPosition;
varying vec4 v_surfaceColor;
varying vec2 v_texCoord;

vec4 BlendTextureAndColor(vec4 color, vec4 textureColor)
{
	vec4 newColor;
	float blendValue = min(u_useTexture, textureColor.a);
	newColor.r = color.r * (1.0 - blendValue) + textureColor.r * blendValue;
	newColor.g = color.g * (1.0 - blendValue) + textureColor.g * blendValue;
	newColor.b = color.b * (1.0 - blendValue) + textureColor.b * blendValue;
	newColor.a = max(color.a, textureColor.a);
	return newColor;
}

void main()
{
	vec4 diffuseTexel;
	diffuseTexel = texture2D(u_diffuseTexture, v_texCoord);
	vec4 newColor;
	newColor = BlendTextureAndColor(v_surfaceColor, diffuseTexel);
	gl_FragColor = newColor;
}

