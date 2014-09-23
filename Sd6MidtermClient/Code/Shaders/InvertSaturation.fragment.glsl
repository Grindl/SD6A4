#version 330

//
//
//
//
//
//

uniform vec3 u_cameraPositionWorldSpace;
uniform vec3 u_cameraDirectionVector;
	struct light{
	vec3 position;
	vec4 colorAndBrightness;
	vec3 direction;
	float innerRadius;
	float outerRadius;
	float innerApertureDot;
	float outerApertureDot;
	float fractionAmbient;
	};


const int SIZEOF_LIGHT = 15;
const int NUM_LIGHTS_SUPPORTED = 16;
//HACK GLSL does not support Enums, and these offsets need meaning
const int xposOffset = 0;
const int yposOffset = 1;
const int zposOffset = 2;
const int redOffset = 3;
const int greenOffset = 4;
const int blueOffset = 5;
const int alphaOffset = 6;
const int xdirOffset = 7;
const int ydirOffset = 8;
const int zdirOffset = 9;
const int innerRadiusOffset = 10;
const int outerRadiusOffset = 11;
const int innerApertureOffset = 12;
const int outerApertureOffset = 13;
const int fractionAmbientOffset = 14;

//layout(std140) uniform LightBlock
//{
//	light u_lights[16];
//};
uniform float u_lights[NUM_LIGHTS_SUPPORTED*SIZEOF_LIGHT];
//uniform float u_lights[SIZEOF_LIGHT*NUM_LIGHTS_SUPPORTED];

uniform sampler2D u_diffuseTexture;
uniform bool u_useTexture;
uniform sampler2D u_normalTexture;
uniform bool u_useNormal;
uniform vec3 u_lightVector;
//uniform vec3 u_lightColor
uniform bool u_showSpecular;
uniform sampler2D u_specularTexture;
uniform bool u_useSpecular;
uniform sampler2D u_emissiveTexture;
uniform bool u_useEmissive;

//uniform bool u_useFog;
//uniform float u_fogStart;
//uniform float u_fogEnd;
//uniform float u_fogStrengthAtEnd;
//uniform vec4 u_fogColor;

//in vec3 v_screenPosition;
in vec3 v_worldPosition;

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;

out vec4 fragmentColor;

in vec4 v_surfaceColor;
in vec2 v_texCoord;
in vec3 v_tangent;
in vec3 v_bitangent;
in vec3 v_normal;


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

vec4 invertSaturation(vec4 colorIn)
{
	vec4 newColor, greyscale, saturationDifference;
	greyscale = GetAsGreyscale(colorIn);
	saturationDifference = colorIn - greyscale;
	newColor = greyscale - saturationDifference*.5;
	return newColor;
}

void main()
{
	
	vec3 worldNormalVector = v_normal;
	fragmentColor = vec4(0,0,0,0);

	for(int ii = 0; ii < NUM_LIGHTS_SUPPORTED; ii++)
	{//BEGIN LIGHT LOOP

	vec4 baseColor;
	vec3 lightPosition = vec3(u_lights[ii*SIZEOF_LIGHT+xposOffset], u_lights[ii*SIZEOF_LIGHT+yposOffset], u_lights[ii*SIZEOF_LIGHT+zposOffset]);
	vec3 lightVector = lightPosition - v_worldPosition;
	vec3 lightVectorNormed = normalize(lightVector);
	vec3 lightDirectionNormed = normalize(vec3(u_lights[ii*SIZEOF_LIGHT+xdirOffset], u_lights[ii*SIZEOF_LIGHT+ydirOffset], u_lights[ii*SIZEOF_LIGHT+zdirOffset]));
	float lightAngleDot = dot(lightVectorNormed, lightDirectionNormed);
	float lightDistanceStrength = clamp(max(u_lights[ii*SIZEOF_LIGHT+outerRadiusOffset] - length(lightVector), 0) / max(u_lights[ii*SIZEOF_LIGHT+outerRadiusOffset] - u_lights[ii*SIZEOF_LIGHT+innerRadiusOffset], 0.01), 0, 1);
	float lightDirectionStrength = clamp(max(lightAngleDot - u_lights[ii*SIZEOF_LIGHT+innerApertureOffset], 0) / max(u_lights[ii*SIZEOF_LIGHT+innerApertureOffset] - u_lights[ii*SIZEOF_LIGHT+outerApertureOffset], 0.01), 0, 1);
	float lightTotalBrightness = lightDistanceStrength * lightDirectionStrength * u_lights[ii*SIZEOF_LIGHT+alphaOffset];


	if(u_useTexture)
	{
		vec4 texColor = texture2D(u_diffuseTexture, v_texCoord);
		baseColor = v_surfaceColor * texColor;
	}
	else
	{
		baseColor = v_surfaceColor;
	}

	if(u_useNormal)
	{
		vec3 normals = texture2D(u_normalTexture, v_texCoord).rgb;
		//normals = normalize(normals);
		normals = (normals * 2) - vec3(1,1,1);
		vec3 newBitangent = v_bitangent * -1;
		mat3 worldVectors = mat3(v_tangent, newBitangent, v_normal);
		mat3 worldVectorsTransposed = transpose(worldVectors);		
		worldNormalVector = normals*worldVectorsTransposed;
		float lightVal = dot(lightVectorNormed, worldNormalVector)*(1-u_lights[ii*SIZEOF_LIGHT+fractionAmbientOffset]) + u_lights[ii*SIZEOF_LIGHT+fractionAmbientOffset];
		float normalFeathering = dot(v_normal, lightVector) * 5.0;
		normalFeathering = clamp(normalFeathering, 0, 1);
		normalFeathering += (u_lights[ii*SIZEOF_LIGHT+fractionAmbientOffset]);
		normalFeathering = clamp(normalFeathering, 0, 1);
		lightVal *= normalFeathering;
		baseColor.rgb = baseColor.rgb * lightVal * vec3(u_lights[ii*SIZEOF_LIGHT+redOffset], u_lights[ii*SIZEOF_LIGHT+greenOffset], u_lights[ii*SIZEOF_LIGHT+blueOffset]) * lightTotalBrightness;
	}

	if(u_showSpecular)
	{
		//Specular color = pow(max(dot(PtoL, I),0), 1+(MAXSPECPOWER * glossiness)) * Specular Intensity * light color * light brightness
		vec3 specularColor;
		float specularPower = 16.0;
		float specularGlossiness = .50;
		if(u_useSpecular)
		{
			vec4 specularData = texture2D(u_specularTexture, v_texCoord);
			specularPower = (specularData.r*32.0)+1;
			specularGlossiness = specularData.g;
		}
		vec3 idealLightVector = reflect(v_worldPosition - u_cameraPositionWorldSpace, worldNormalVector);
		idealLightVector = normalize(idealLightVector);
		//TODO confirm light color works
		specularColor = pow(max(dot(lightVectorNormed, idealLightVector), 0), specularPower) * specularGlossiness * vec3(u_lights[ii*SIZEOF_LIGHT+redOffset], u_lights[ii*SIZEOF_LIGHT+greenOffset], u_lights[ii*SIZEOF_LIGHT+blueOffset]) * lightTotalBrightness;
		float specularFeathering = dot(v_normal, lightVector) * 5.0;
		specularFeathering = clamp(specularFeathering, 0, 1);
		specularFeathering += (u_lights[ii*SIZEOF_LIGHT+fractionAmbientOffset]);
		specularFeathering = clamp(specularFeathering, 0, 1);
		specularColor *= specularFeathering;
		baseColor = baseColor + vec4(specularColor, 0.0);
	}

	//vec4 emissiveColor = vec4(0,0,0,0);


	clamp(baseColor, 0,1);
	fragmentColor +=baseColor;
	//if(ii == 2)
	//{
	//	fragmentColor = vec4(length(lightVector)/5, length(lightVector)/5, length(lightVector)/5, 1);
	//}
	}//END LIGHT LOOP
	//fragmentColor.rgb = u_lights[0].position + emissiveColor.rgb;
	//fragmentColor.a = 1;

	if(u_useEmissive)
	{
		vec4 emissiveColor = texture2D(u_emissiveTexture, v_texCoord);
		fragmentColor = fragmentColor + emissiveColor;
	}

	//HACK
	bool u_useFog = false;
	float u_fogStart = 1.f;
	float u_fogEnd = 10.f;
	float u_fogStrengthAtEnd = .9f;
	vec4 u_fogColor = vec4(0,0,0,1);

	if(u_useFog)
	{
		float cameraToPointDistance = length(u_cameraPositionWorldSpace - v_worldPosition);
		float fogPower = clamp(max(cameraToPointDistance - u_fogStart, 0) / max(u_fogEnd - u_fogStart, 0.01) * u_fogStrengthAtEnd, 0, 1);
		fragmentColor = fragmentColor * (1 - fogPower) + u_fogColor * fogPower;
	}
	fragmentColor = invertSaturation(fragmentColor);
}