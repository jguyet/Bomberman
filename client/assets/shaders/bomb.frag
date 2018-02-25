#version 330

layout (std140) uniform u_material {
	vec4 diffuse;
	vec4 ambient;
	vec4 specular;
	vec4 emissive;
	float shininess;
	int texCount;
};

uniform	sampler2D u_texUnit;
uniform vec3 u_color_bomb;
uniform vec3 u_color_meche;

in vec3 v_norm;

out vec4 o_color;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec4 diffusem = vec4(diffuse);
	if (diffusem.x < 0.2 && diffusem.y < 0.2 && diffusem.y < 0.2) { //BOMB
		diffusem = vec4(0.3,0.3,0.3,1);
	} else { //MECHE
		diffusem = vec4(0.8,0.1,0.1,1);
	}
	vec3 lightDir = normalize(vec3(0,0,1.0));

	float ndotl = dot(v_norm, lightDir);
	vec3 vdiffuse = vec3(diffusem.xyz) * clamp(ndotl, 0, 1.0);

	o_color = vec4(vdiffuse.xyz, 1);
}
