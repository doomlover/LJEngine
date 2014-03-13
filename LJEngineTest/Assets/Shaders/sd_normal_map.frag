#version 120

// MATERIAL
uniform vec3 material_diffuse;
uniform vec3 material_specular;
uniform vec3 material_emission;

uniform sampler2D normal_map;
uniform sampler2D texture_map;
uniform sampler2D emission_map;
uniform sampler2D specular_map;

// DIRECTIONAL LIGHT
uniform vec3 directional_intensity;
uniform vec3 directional_direction;

// AMBIENT LIGHT
uniform vec3 ambient_intensity;

// IN
varying vec2 v_uv;
varying vec3 v_light_dir_tan;
varying vec3 v_normal;
//varying vec3 v_light_dir_eye;
varying vec3 v_eye_dir;

uniform mat4 mat4_mv;

void main() {

	//vec3 normal_world = normalize(v_normal);
	//float ndotl_world = max(dot(normal_world, directional_direction),0);

	// MAX{N dot L, 0}
	vec3 normal = normalize(texture2D(normal_map, v_uv).xyz);
	vec3 light_dir_tan_nor = normalize(v_light_dir_tan);
	float ndotl = max(dot(normal, light_dir_tan_nor), 0.0);
	
	vec3 diffuse = vec3(0,0,0);
	vec3 specular = vec3(0,0,0);
	
	// EM
	vec3 emission = vec3(0,0,0);
	
	// DTA + DTC*NdotL
	diffuse = material_diffuse*texture2D(texture_map, v_uv).xyz*directional_intensity*ndotl+
			material_diffuse*texture2D(texture_map, v_uv).xyz*ambient_intensity;
	          
	// SGC*HdotN
	vec3 H = normalize(v_light_dir_tan+v_eye_dir);
	float ndoth = max(dot(normal, H), 0);
	specular = material_specular*texture2D(specular_map, v_uv).xyz*directional_intensity*ndoth;
	/*
	gl_FragColor.xyz = diffuse + specular;
	gl_FragColor.w = 1.0;
	*/
	// output to GL_COLOR_ATTACHMENT0
	gl_FragData[0].xyz = diffuse + specular;
	gl_FragData[0].w = 1.0;
}


