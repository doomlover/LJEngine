#version 120

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexcoord;
attribute vec4 inTangent;

uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ViewMatrix;
uniform mat4 WorldMatrix;
uniform vec3 CameraPosition;

varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexcoord;

struct lightInfo
{
	vec4 position; // in world
	vec3 intensity;
};
uniform lightInfo light;

varying vec3 vL; // light dir in tangent
varying vec3 vV; // view dir in tangent

void main()
{
	gl_Position = WorldViewProjectionMatrix * vec4(inPosition, 1.0);
	
	// to eye
	vPosition = vec3(WorldViewMatrix * vec4(inPosition, 1.0));
	vNormal = normalize(NormalMatrix * inNormal);
	vec3 tangent = normalize(vec3(NormalMatrix * inTangent.xyz));
	vec3 btangent = normalize(cross(vNormal, tangent)*inTangent.w);

	// eye to tangent
	mat3 TBN = mat3(
		tangent.x, btangent.x, vNormal.x,
		tangent.y, btangent.y, vNormal.y,
		tangent.z, btangent.z, vNormal.z
	);
	
	vTexcoord = inTexcoord;
	
	vec3 light_eye = vec3(ViewMatrix * light.position);
	
	vL = normalize(TBN * (light_eye - vPosition.xyz));
	
	vV = normalize(TBN * (-vPosition.xyz));
}

