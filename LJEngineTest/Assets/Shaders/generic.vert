#version 400

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexcoord;

uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ViewMatrix;

varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexcoord;

struct lightInfo
{
	vec3 position;
	vec3 intensity;
};
uniform lightInfo light;
varying vec3 light_pos;
void main()
{
	gl_Position = WorldViewProjectionMatrix * vec4(inPosition, 1.0);
	
	vPosition = (WorldViewMatrix * vec4(inPosition, 1.0)).xyz;
	vNormal = (NormalMatrix*inNormal);
	vTexcoord = inTexcoord;

	light_pos = vec3(ViewMatrix * vec4(light.position, 1.0));
}

