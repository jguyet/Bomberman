#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;


// Ouput data
out vec3 color;

uniform sampler2D myTextureSampler;

void main(){
	color = texture( myTextureSampler, UV ).rgb;
}
