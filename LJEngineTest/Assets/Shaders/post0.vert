#version 400

in vec3 inPosition;
out vec2 vTexcoord;

void main()
{
	gl_Position = vec4(inPosition, 1.0);
	vTexcoord = inPosition.xy;
}