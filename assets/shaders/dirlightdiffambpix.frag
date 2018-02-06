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

in vec3 v_norm;
in vec3 v_texCoord;

out vec4 o_color;

void main()
{

	vec3 lightDir = normalize(vec3(1.0,1.0,1.0));

	float ndotl = dot(v_norm, lightDir);
	vec3 vdiffuse = vec3(diffuse.xyz) * clamp(ndotl, 0.0, 1.0);
	vec4 color;
	vec3 amb;

	if (texCount == 0) {
		color = vec4(vdiffuse.xyz, 1.0);
	}
	else {
		color = texture(u_texUnit, v_texCoord.xy) * vec4(vdiffuse, 1.0);
	}

	o_color = color;
}
