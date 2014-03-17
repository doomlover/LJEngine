#version 400

varying vec3 vReflectDir;
varying vec3 vRefractDir;

uniform samplerCube cubeMap;

uniform bool DrawSkyBox;

struct MaterialInfo
{
	float Eta;
	float ReflectionFactor;
};
uniform MaterialInfo Material;

void main()
{
	vec4 reflect = textureCube(cubeMap, vReflectDir);
	if(DrawSkyBox)
		gl_FragColor = reflect;
	else
	{
		vec4 refract = textureCube(cubeMap, vRefractDir);
		gl_FragColor = mix(refract, reflect, Material.ReflectionFactor);
	}
}