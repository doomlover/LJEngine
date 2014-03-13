#version 120
varying vec3 vFrontColor;
varying vec3 vBackColor;
varying vec2 vTexcoord;

void main()
{
	const float scale = 15.0;
	bvec2 toDiscard = greaterThan(fract(vTexcoord * scale), vec2(0.2, 0.2));
	//if(all(toDiscard)) discard;	
	
	if(gl_FrontFacing)
	{
		gl_FragColor = vec4(vFrontColor, 1.0);
	}
	else
	{
		gl_FragColor = vec4(vBackColor, 1.0);
	}
	
}
