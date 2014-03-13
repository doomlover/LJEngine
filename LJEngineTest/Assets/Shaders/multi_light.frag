#version 120
varying vec3 vFrontColor;
varying vec3 vBackColor;
varying vec2 vTexcoord;

void main()
{
	if(gl_FrontFacing)
	{
		gl_FragColor = vec4(vFrontColor, 1.0);
	}
	else
	{
		gl_FragColor = vec4(vBackColor, 1.0);
	}
	
}