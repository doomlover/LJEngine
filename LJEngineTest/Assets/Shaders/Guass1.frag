#version 400

in vec2 vTexcoord;

uniform sampler2D renderTex1;
uniform unsigned int WindowHeight;

uniform float PixOffset[5] = float[](0.0,1.0,2.0,3.0,4.0);
uniform float Weight[5];

vec4 Guass1()
{
	float dy = 1.0 / float(WindowHeight);

	vec4 sum = texture2D(renderTex1, vTexcoord) * Weight[0];

	for(int i = 1; i < 5; ++i)
	{
		sum += texture2D(renderTex1, vTexcoord + vec2(0.0, PixOffset[i])*dy) * Weight[i];
		sum += texture2D(renderTex1, vTexcoord - vec2(0.0, PixOffset[i])*dy) * Weight[i];
	}
	return sum;
}

void main()
{
	gl_FragColor = Guass1();
}