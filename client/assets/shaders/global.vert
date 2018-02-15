#version 330

in vec3 a_pos;
in vec3 a_norm;
in vec3 a_texCoord;

uniform mat4 u_projMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_modelMatrix;
uniform mat4 u_transformMatrix;

out vec3 v_pos;
out vec3 v_norm;
out vec3 v_texCoord;

void main()
{
	vec4 mpos = (u_projMatrix * u_viewMatrix * u_modelMatrix) * vec4(a_pos, 1.0);

	v_pos = a_pos;
	v_norm = vec4((u_viewMatrix * u_modelMatrix) * vec4(a_norm, 0.0)).xyz;
	v_texCoord = a_texCoord;

	gl_Position = mpos;
}
