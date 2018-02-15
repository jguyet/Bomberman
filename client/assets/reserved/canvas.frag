#version 330

uniform	sampler2D u_texUnit;

in vec2 v_texCoord;

out vec4 o_color;

void main()
{
	vec3 color = texture(u_texUnit, v_texCoord.xy).xyz;

	if (color.x == 0 && color.y == 0.00392156863 && color.z == 0)
	{
		discard;
	}
	else
	{
		o_color = vec4(color.xyz,1);
	}
}
