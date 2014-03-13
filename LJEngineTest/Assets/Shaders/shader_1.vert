#version 120

attribute vec3 inPosition;
attribute vec2 inUV;

varying vec2 vUV;
uniform mat4 MVP;


void main() {
	gl_Position = MVP * vec4(inPosition, 1.0);
	
	vUV = inUV;
}