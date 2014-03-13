#version 120

#ifndef NUM_LIGHTS
#define NUM_LIGHTS 1
#endif

varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexcoord;

uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;

uniform bool UseColor = true;
uniform vec3 Color;

uniform bool UseDiffuseMap = false;
uniform sampler2D diffuseMap; 

struct lightInfo
{
	vec3 position;
	vec3 intensity;
};
uniform lightInfo light;
varying vec3 light_pos;
struct materialInfo
{
	vec3 kd;
	vec3 ka;
	vec3 ks;
	int exp;
};
uniform materialInfo material;

vec3 phongMode(int lightIndex, vec3 pos, vec3 nor)
{
	vec3 l = normalize(light_pos.xyz-pos);
	vec3 v = normalize(vec3(-pos));
	vec3 h = normalize(v + l);
	
	return light.intensity * (material.kd * max(dot(nor, l), 0.0) + 
										  material.ka + 
										  material.ks * pow(max(dot(nor, h), 0.0), material.exp));
}

void main()
{
	vec3 pos;
	vec3 nor;

	pos  = vPosition;
	nor = normalize(vNormal);
	vec3 color = phongMode(0, pos, nor);
	if(UseColor)
		color *= Color;
	if(UseDiffuseMap)
	{
		color *= texture2D(diffuseMap, vTexcoord).xyz;
	} 
	gl_FragColor = vec4(color, 1.0);
}
