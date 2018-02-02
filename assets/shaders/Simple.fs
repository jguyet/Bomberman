#version 330 core

out vec3 color;
in vec3 fragmentColor;

void main()
{

	// Output color = red
	//color = vec4(1,0,0,1);
	color = fragmentColor;
}
