#version 120

#ifndef NUM_LIGHTS
#define NUM_LIGHTS 2
#endif

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexcoord;

struct lightInfo
{
	vec4 position;
	vec3 intensity;
};
uniform lightInfo light[NUM_LIGHTS];

struct materialInfo
{
	vec3 kd;
	vec3 ka;
	vec3 ks;
	int exp;
};
uniform materialInfo material;

uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;

void getEyeSpace(out vec4 position, out vec3 normal)
{
	position = (WorldViewMatrix * vec4(inPosition, 1.0));
	normal = normalize(NormalMatrix * inNormal);
}

vec3 phongMode(int lightIndex, vec4 pos, vec3 nor)
{
	vec3 l_dir_eye;
	if(light[lightIndex].position.w == 0.0)
	{
		l_dir_eye = normalize(light[lightIndex].position.xyz);
	}
	else
	{
		l_dir_eye = normalize(light[lightIndex].position.xyz - pos.xyz);
	}
	float n_dot_l = max(dot(nor, l_dir_eye), 0.0);
	
	vec3 v_dir_eye = normalize(vec3(-pos));
	vec3 half_dir = normalize(v_dir_eye + l_dir_eye);
	float n_dot_h = max(dot(nor, half_dir), 0.0);
	
	return light[lightIndex].intensity * (material.kd * n_dot_l + 
										material.ka + 
										material.ks * pow(n_dot_l, material.exp));
}

varying vec3 vFrontColor;
varying vec3 vBackColor;
varying vec2 vTexcoord;

void main()
{
	gl_Position = WorldViewProjectionMatrix * vec4(inPosition, 1.0);
	vec4 ePos;
	vec3 eNor;
	getEyeSpace(ePos, eNor);
	vFrontColor = vec3(0.0, 0.0, 0.0);
	vBackColor = vec3(0.0, 0.0, 0.0);
	for(int i = 0; i < NUM_LIGHTS; ++i)
	{
		vFrontColor += phongMode(i, ePos, eNor);
		vBackColor += phongMode(i, ePos, -eNor);
	}
	vTexcoord = inTexcoord;
}