#version 400

in vec2 vTexcoord;

uniform sampler2D renderTex1;
uniform unsigned int WindowWidth;

uniform float PixOffset[5] = float[](0.0,1.0,2.0,3.0,4.0);
uniform float Weight[5];

vec4 Guass1()
{
	float dx = 1.0 / float(WindowWidth);

	vec4 sum = texture2D(renderTex1, vTexcoord) * Weight[0];

	for(int i = 1; i < 5; ++i)
	{
		sum += texture2D(renderTex1, vTexcoord + vec2(PixOffset[i], 0.0)*dx) * Weight[i];
		sum += texture2D(renderTex1, vTexcoord - vec2(PixOffset[i], 0.0)*dx) * Weight[i];
	}
	return sum;
}

void main()
{
	gl_FragColor = Guass1();
}