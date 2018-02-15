#version 330

in vec3 a_pos;
in vec2 a_texCoord;

out vec2 v_texCoord;

void main()
{
	v_texCoord = a_texCoord;
	v_texCoord.x = -v_texCoord.x;
	vec3 pos = a_pos;

	gl_Position = vec4(pos.xy,0,1);
}
