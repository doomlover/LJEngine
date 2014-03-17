#version 400

in vec2 vTexcoord;

uniform sampler2D renderTex;
uniform unsigned int WindowWidth;
uniform unsigned int WindowHeight;

float EdgeThreshold = 0.025;

float luma(vec3 color)
{
	return 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
}
vec4 EdgeFilter()
{
	float dx = 1.0 / float(WindowWidth);
	float dy = 1.0 / float(WindowHeight);

	float s00 = luma(texture2D(renderTex, vTexcoord + vec2(-dx, dy)).rgb);
	float s01 = luma(texture2D(renderTex, vTexcoord + vec2(0.0, dy)).rgb);
	float s02 = luma(texture2D(renderTex, vTexcoord + vec2(dx, dy)).rgb);

	float s10 = luma(texture2D(renderTex, vTexcoord + vec2(-dx, 0.0)).rgb);
	float s12 = luma(texture2D(renderTex, vTexcoord + vec2(dx, 0.0)).rgb);

	float s20 = luma(texture2D(renderTex, vTexcoord + vec2(-dx, -dy)).rgb);
	float s21 = luma(texture2D(renderTex, vTexcoord + vec2(0.0, -dy)).rgb);
	float s22 = luma(texture2D(renderTex, vTexcoord + vec2(dx, -dy)).rgb);

	float sx = s00 + 2*s10 + s20 - (s02 + 2*s12 + s22);
	float sy = s00 + 2*s01 + s02 - (s20 + 2*s21 + s22);
	float dist = sx*sx + sy*sy;
	if(dist > EdgeThreshold)
	{
		return vec4(1.0);
	}
	else
	{
		return vec4(0.0, 0.0, 0.0, 1.0);
	}
}

void main()
{
	gl_FragColor = EdgeFilter();
	//gl_FragColor = texture2D(renderTex, vTexcoord);
}