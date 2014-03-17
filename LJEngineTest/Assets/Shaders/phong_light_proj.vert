#version 400

attribute vec3 inPosition;
attribute vec3 inNormal;
attribute vec2 inTexcoord;

uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 WorldMatrix;
uniform mat4 ViewMatrix;

varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexcoord;

// projector matrix
uniform mat4 ProjectorMatrix;
// project texture coord
varying vec4 vProjectorCoord;

void main()
{
	gl_Position = WorldViewProjectionMatrix * vec4(inPosition, 1.0);

	vProjectorCoord = ProjectorMatrix * WorldMatrix * vec4(inPosition, 1.0);
}

