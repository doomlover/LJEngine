#version 120
attribute vec3 inPosition;
attribute vec3 inNormal;

//subroutine vec3 ShaderModeType(vec3 position, vec3 normal);
//subroutine uniform ShaderModeType shaderMode;

uniform vec3 kd;
uniform vec3 ld;
uniform vec3 eye_light_pos;
uniform mat4 WorldViewProjectionMatrix;
uniform mat4 WorldViewMatrix;

//subroutine(ShaderModeType)
vec3 phongMode(vec3 position, vec3 normal)
{
	// eye_light_pos to obj_light_pos
	vec3 obj_light_pos = (WorldViewMatrix * vec4(eye_light_pos, 1.0)).xyz;
	vec3 obj_light_dir = normalize(obj_light_pos - position);
	vec3 obj_normal = normalize(normal);
	float n_dot_l = max(dot(obj_normal, obj_light_dir), 0);
	return kd * n_dot_l;
}

//subroutine(ShaderModeType)
vec3 diffuseOnly(vec3 position, vec3 normal)
{
	return vec3(1.0, 0.0, 0.0);
}

varying vec3 vColor;

void main()
{
	//vColor = shaderMode(inPosition, inNormal);
	vColor = phongMode(inPosition, inNormal);
	gl_Position = WorldViewProjectionMatrix * vec4(inPosition, 1.0); 
}