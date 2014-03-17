#version 400

uniform sampler2D renderTex;

in vec2 vTexcoord;

void main()
{
	gl_FragColor = texture2D(renderTex, vTexcoord);
	//gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
}