#version 120

#ifndef NUM_LIGHTS
#define NUM_LIGHTS 1
#endif

varying vec3 vPosition;
varying vec3 vNormal;

uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;

struct SpotInfo
{
	vec3 position;
	vec3 direction;
	vec3 intensity;
	int exp;
};
uniform SpotInfo light;
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
	vec3 l;
	l = normalize(light.position.xyz - pos.xyz);
	vec3 v = normalize(vec3(-pos));
	vec3 h = normalize(v + l);
	
	float dir_dot_l = max(dot(normalize(-light.direction), l),0);
	float ang = acos(dir_dot_l);
	vec3 amb = light.intensity * material.ka;
	float cut = radians(40.0);
	if(ang < cut)
	{
		float f = pow(dir_dot_l, light.exp);
		return amb + f*light.intensity*(material.kd * max(dot(nor, l), 0.0)+
		material.ks * pow(max(dot(nor, h), 0.0), material.exp));
	}
	else
	{
		return amb;
	}
}

void main()
{
	vec3 pos;
	vec3 nor;

	pos  = vPosition;
	nor = normalize(vNormal);

	vec3 color = phongMode(0, pos, nor);
	
	gl_FragColor = vec4(color, 1.0);
}
