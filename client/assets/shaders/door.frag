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

in vec3 v_texCoord;

out vec4 o_color;

void main()
{
	vec3 vdiffuse = vec3(diffuse.xyz);
	vec4 color;

	//vec4 alpha = texture2D(u_texUnit, v_texCoord).aaaa;

	if (texCount == 0) {
		color = vec4(vdiffuse.xyz, 1.0);
	}
	else {
		color = texture(u_texUnit, v_texCoord.xy) * vec4(vdiffuse, 1.0);
	}

	//color  = color * alpha;

	if (color.x > 0.5 && color.y > 0.5 && color.z > 0.5) {
		discard;
	}

	if (color.x > 0.9 && color.y > 0.9 && color.z > 0.9) {
		discard;
	}

	if (color.x < 0.05 && color.y < 0.05 && color.z < 0.05) {
		discard;
	}

	o_color = color;
}
