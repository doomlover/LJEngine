#version 120

//#import "Assets/lighting.ljsllib"

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexcoord;

uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;

struct lightInfo
{
	vec3 ld;
	vec3 la;
	vec3 ls;
	vec3 l_pos_eye;
};

struct materialInfo
{
	vec3 kd;
	vec3 ka;
	vec3 ks;
	int exp;
};

uniform lightInfo light;
uniform materialInfo material;

void toEyeSpace(out vec3 position, out vec3 normal)
{
	position = (WorldViewMatrix * vec4(inPosition, 1.0)).xyz;
	normal = NormalMatrix * inNormal;
}

vec3 phongMode(vec3 pos, vec3 norm)
{
	// diffuse
	vec3 l_dir_eye = normalize(light.l_pos_eye - pos);
	float n_dot_l = max(dot(normalize(norm), l_dir_eye), 0.0);
	vec3 diff = light.ld * material.kd * n_dot_l;
	//float nDotL = LightDiffuse(pos, normalize(norm), light.l_pos_eye, l_dir_eye);
	//vec3 diff = light.ld * material.kd * nDotL;
	// ambient
	vec3 amb = light.la * material.ka;
	
	// specular
	vec3 eye_dir = normalize(-pos);
	vec3 half_dir = normalize(eye_dir + l_dir_eye);
	float n_dot_h = max(dot(normalize(norm), half_dir), 0.0);
	vec3 spec = light.ls * material.ks * pow(n_dot_h, material.exp);
	
	return diff + amb + spec;
}

vec3 diffuseOnly(vec3 position, vec3 normal)
{
	vec3 obj_light_pos = (vec4(light.l_pos_eye, 1.0)).xyz;
	vec3 obj_light_dir = normalize(obj_light_pos - position);
	vec3 obj_normal = normalize(normal);
	float n_dot_l = max(dot(obj_normal, obj_light_dir), 0);
	return material.kd * n_dot_l;
}

varying vec3 vFrontColor;
varying vec3 vBackColor;
varying vec2 vTexcoord;

void main()
{
	gl_Position = WorldViewProjectionMatrix * vec4(inPosition, 1.0);
	
	vec3 eyePos;
	vec3 eyeNorm;
	toEyeSpace(eyePos, eyeNorm);
	vFrontColor = phongMode(eyePos, eyeNorm);
	vBackColor = phongMode(eyePos, -eyeNorm);
	vTexcoord = inTexcoord;
}
 