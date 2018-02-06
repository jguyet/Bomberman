#version 330

in vec3 a_pos;
in vec3 a_norm;
in vec2 a_texCoord;

uniform mat4 u_projMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;
uniform mat4 u_transformMatrix;

out vec3 v_norm;
out vec2 v_texCoord;

void main()
{
	vec4 mpos = u_modelMatrix * u_viewMatrix * vec4(a_pos, 1.0);

	v_norm = vec4((u_viewMatrix * u_modelMatrix) * vec4(a_norm, 0.0)).xyz;
	v_texCoord = a_texCoord;

	gl_Position = u_projMatrix * mpos;
}
