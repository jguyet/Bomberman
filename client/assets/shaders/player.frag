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

	vec4 diffusem = vec4(diffuse);
	if (diffusem.x == 0.8 && diffusem.y == 0.8 && diffusem.z == 0.8) {//COLOR PLAYER
		diffusem = vec4(0.558,0.034,0.052,1);
	} else if (diffusem.x == 0.658229 && diffusem.y == 0.142446 && diffusem.z == 0.475947) {//COLOR BALLS
		diffusem = vec4(1,1,1,1);
	} else if (diffusem.x == 0.074000 && diffusem.y == 0.237000 && diffusem.z == 0.558400) {//COLOR TISHIRT
		diffusem = vec4(0.558,0.034,0.052,1);
	}

	vec3 lightDir = normalize(vec3(0,0,1.0));

	float ndotl = dot(v_norm, lightDir);
	vec3 vdiffuse = vec3(diffusem.xyz) * clamp(ndotl, 0, 1.0);

	o_color = vec4(vdiffuse.xyz, 1);
}
