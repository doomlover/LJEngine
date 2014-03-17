#version 400


varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vTexcoord;

// project texture
uniform sampler2D projectMap;
// project texture coord
varying vec4 vProjectorCoord;


void main()
{
	vec4 projColor = vec4(0.0);
	if(vProjectorCoord.z > 0.0)
		projColor = texture2D(projectMap, vProjectorCoord.xy/vProjectorCoord.w)*0.5;
	gl_FragColor = vec4(1.0, 0.5, 0.5, 1.0) + projColor;
}
