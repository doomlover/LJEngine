#version 120

// IN
attribute vec3 aPosition;
attribute vec3 aColor;
attribute vec2 aTexCoord;
attribute vec3 aNormal;
attribute vec4 aTangent;

uniform vec3 u_dlight_direction;
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 V;
uniform mat4 M;
uniform mat4 InverseV;

// OUT
varying vec2 v_uv;
//varying vec3 v_light_dir_eye;
varying vec3 v_light_dir_tan;
varying vec3 v_eye_dir;
//varying vec3 v_normal;

void main() {
	gl_Position = MVP * vec4(aPosition, 1.0);
	
	vec3 normal = normalize(aNormal);
	vec3 B = aTangent.w * normalize(cross(normal, aTangent.xyz));
	/*
	vec3 normal_eye = normalize((M*vec4(aNormal,1)).xyz);
	vec3 T_eye = normalize((M*aTangent).xyz);
	vec3 B_eye = normalize(aTangent.w*cross(normal_eye, T_eye));
	
	mat3 toTangentEye = mat3(
	T_eye.x, B_eye.x, normal_eye.x,
	T_eye.y, B_eye.y, normal_eye.y,
	T_eye.z, B_eye.z, normal_eye.z);
	
	v_light_dir_tan = (toTangentEye * directional_direction);
	*/

	mat3 toTangentObj = mat3(
	aTangent.x, B.x, normal.x,
	aTangent.y, B.y, normal.y,
	aTangent.z, B.z, normal.z);

	vec3 directional_direction_model = (mat4_inverse_m*vec4(directional_direction,1.0)).xyz;
	v_light_dir_tan =(toTangentObj * directional_direction_model);	
	
	vec3 pos_eye = (mat4_mv*vec4(inPosition, 1.0)).xyz;
	vec3 eye_dir_model = (mat4_inverse_mv*vec4(-pos_eye,1.0)).xyz;
	v_eye_dir = (toTangentObj * eye_dir_model);

	//v_light_dir_eye = (mat4_v*vec4(directional_direction, 1.0)).xyz;
	v_uv = inUV;
	//v_normal = (mat4_m*vec4(inNormal,1.0)).xyz;
}


