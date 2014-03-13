#version 120

varying vec2 vUV;

uniform sampler2D sampler0;

void main() {
	
	//vec3 material_ambient = texture2D(sampler0, vUV).xyz;

//	gl_FragColor.xyz = texture2D(sampler0, vUV).xyz;
	gl_FragColor.xyz = vec3(1.0, 0.0, 1.0);
	gl_FragColor.w = 1.0;
}
