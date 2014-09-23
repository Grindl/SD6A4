#version 330

// Vertex Shader, GLSL v 3.30
// Designed to replace the fixed fucntion pipeline, supports only diffuse texturing
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

uniform float u_lights[NUM_LIGHTS_SUPPORTED*SIZEOF_LIGHT];


uniform sampler2D u_diffuseTexture;
uniform bool u_useTexture;
uniform sampler2D u_normalTexture;
uniform bool u_useNormal;
uniform vec3 u_lightVector;
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

//out vec3 v_screenPosition;
out vec3 v_worldPosition;

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;

in vec3 v_vertex;
in vec4 v_colorIn;
in vec2 v_texCoordIn;
in vec3 v_tangentIn;
in vec3 v_bitangentIn;
in vec3 v_normalIn;


out vec4 v_surfaceColor;
out vec2 v_texCoord;
out vec4 gl_Position;
out vec3 v_tangent;
out vec3 v_bitangent;
out vec3 v_normal;

void main()
{
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	//v_screenPosition = gl_Position;
	//v_worldPosition = gl_Vertex;
	//v_surfaceColor = gl_Color;
	//v_texCoord = gl_MultiTexCoord0.xy;
	vec4 vertTemp = vec4(v_vertex, 1.0);
	gl_Position = u_projectionMatrix * u_modelViewMatrix * vertTemp;
	//v_screenPosition = gl_Position.xyz;
	v_worldPosition = v_vertex;
	v_surfaceColor = v_colorIn;
	v_texCoord = v_texCoordIn;

	v_tangent = v_tangentIn;
	v_bitangent = v_bitangentIn;
	v_normal = v_normalIn;
}
	
	
