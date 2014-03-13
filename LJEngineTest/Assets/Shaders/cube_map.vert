#version 120
// device input/output
attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexcoord;

uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ViewMatrix;
uniform mat4 WorldMatrix;
uniform vec3 CameraPosition;

varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexcoord;

// use input/output
varying vec3 vReflectDir;
varying vec3 vRefractDir;
uniform bool DrawSkyBox;

struct MaterialInfo
{
	float Eta;
	float ReflectionFactor;
};
uniform MaterialInfo Material;

void main()
{
	gl_Position = WorldViewProjectionMatrix * vec4(inPosition, 1.0);
	if(DrawSkyBox)
		vReflectDir = inPosition;
	else {
	vec3 wPos = vec3(WorldMatrix * vec4(inPosition, 1.0));
	vec3 wNor = vec3(WorldMatrix * vec4(inNormal, 0.0));
	vec3 wView = normalize(CameraPosition - wPos);
	vReflectDir = reflect(-wView, wNor);
	vRefractDir = refract(-wView, wNor, Material.Eta);
	}
}

