#version 400

#ifndef NUM_LIGHTS
#define NUM_LIGHTS 1
#endif

varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexcoord;

varying vec3 vL;
varying vec3 vV;
varying vec3 vLight;
varying vec3 vCam;

uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ViewMatrix;

uniform sampler2D normalMap;
uniform sampler2D diffuseMap;

struct lightInfo
{
	vec4 position;
	vec3 intensity;
};
uniform lightInfo light;

struct materialInfo
{
	vec3 kd;
	vec3 ka;
	vec3 ks;
	int exp;
};
uniform materialInfo material;

vec3 phongMode(int lightIndex, vec3 diff, vec3 nor)
{
	vec3 l = vL;
	vec3 v = vV;
	vec3 h = normalize(l + v);
	float n_dot_l = max(dot(nor, l), 0.0);
	vec3 diffuse = light.intensity * material.kd * n_dot_l;
	vec3 ambient = light.intensity * material.ka ;
	vec3 spec = vec3(0.0);
	if(n_dot_l > 0.0)
	{
		spec =  light.intensity * material.ks * pow(max(dot(nor, h), 0.0), material.exp);
	}
	return diffuse + ambient + spec;
}

void main()
{
	vec3 nor;
	vec4 texel = texture2D(diffuseMap, vTexcoord);
	nor = normalize(texture2D(normalMap, vTexcoord).xyz);

	vec3 color = phongMode(0, texel.xyz, nor);
	
	
	
	gl_FragColor = vec4(color, 1.0);
}
