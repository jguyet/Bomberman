#include "Bomberman.hpp"

// STATIC ########################################################

// ###############################################################

// CANONICAL #####################################################

Cube::Cube ( void )
{
	return ;
}

Cube::Cube ( float x, float y, float z, float scale )
{
	this->pos = glm::vec3(x,y,z);
	this->scale = scale;
	return ;
}

Cube::Cube ( Cube const & src )
{
	*this = src;
	return ;
}

Cube &				Cube::operator=( Cube const & rhs )
{
	if (this != &rhs)
	{
		// make stuff
	}
	return (*this);
}

Cube::~Cube ( void )
{
	return ;
}

// ###############################################################

// CONSTRUCTOR POLYMORPHISM ######################################

// ###############################################################

// OVERLOAD OPERATOR #############################################

std::ostream &				operator<<(std::ostream & o, Cube const & i)
{
	(void)i;
	return (o);
}

void 									Cube::build_position(void)
{
	float x = this->pos.x;
	float y = this->pos.y;
	float z = this->pos.z;
	float scale = this->scale / 2;

	GLfloat vertex_buffer_data2[] = {

		x +  scale, y + scale, z + -scale,//back
		x +  scale, y + -scale, z + -scale,
		x + -scale, y + -scale, z + -scale,
		x +  scale, y +  scale, z + -scale,
		x + -scale, y + -scale, z + -scale,
		x + -scale, y +  scale, z + -scale,

		x + -scale, y + -scale, z + -scale,//left
		x + -scale, y + -scale, z +  scale,
		x + -scale, y +  scale, z +  scale,
		x + -scale, y + -scale, z + -scale,
		x + -scale, y +  scale, z +  scale,
		x + -scale, y +  scale, z + -scale,

		x + -scale, y +  scale, z +  scale,//face
		x + -scale, y + -scale, z +  scale,
		x +  scale, y + -scale, z +  scale,
		x +  scale, y +  scale, z +  scale,
		x + -scale, y +  scale, z +  scale,
		x +  scale, y + -scale, z +  scale,

		x +  scale, y +  scale, z +  scale,//right
		x +  scale, y + -scale, z + -scale,
		x +  scale, y +  scale, z + -scale,
		x +  scale, y + -scale, z + -scale,
		x +  scale, y +  scale, z +  scale,
		x +  scale, y + -scale, z +  scale,

		x +  scale, y +  scale, z +  scale,//top
		x +  scale, y +  scale, z + -scale,
		x + -scale, y +  scale, z + -scale,
		x +  scale, y +  scale, z +  scale,
		x + -scale, y +  scale, z + -scale,
		x + -scale, y +  scale, z +  scale,

		x +  scale, y + -scale, z +  scale,//down
		x + -scale, y + -scale, z + -scale,
		x +  scale, y + -scale, z + -scale,
		x +  scale, y + -scale, z +  scale,
		x + -scale, y + -scale, z +  scale,
		x + -scale, y + -scale, z + -scale,
	};

	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data2), vertex_buffer_data2, GL_STATIC_DRAW);

}

void 									Cube::build_color( void )
{
	// One color for each vertex. They were generated randomly.
	GLfloat g_color_buffer_data[] = {
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
		0.822f,  0.569f,  0.201f,
		0.435f,  0.602f,  0.223f,
		0.310f,  0.747f,  0.185f,
		0.597f,  0.770f,  0.761f,
		0.559f,  0.436f,  0.730f,
		0.359f,  0.583f,  0.152f,
		0.483f,  0.596f,  0.789f,
		0.559f,  0.861f,  0.639f,
		0.195f,  0.548f,  0.859f,
		0.014f,  0.184f,  0.576f,
		0.771f,  0.328f,  0.970f,
		0.406f,  0.615f,  0.116f,
		0.676f,  0.977f,  0.133f,
		0.971f,  0.572f,  0.833f,
		0.140f,  0.616f,  0.489f,
		0.997f,  0.513f,  0.064f,
		0.945f,  0.719f,  0.592f,
		0.543f,  0.021f,  0.978f,
		0.279f,  0.317f,  0.505f,
		0.167f,  0.620f,  0.077f,
		0.347f,  0.857f,  0.137f,
		0.055f,  0.953f,  0.042f,
		0.714f,  0.505f,  0.345f,
		0.783f,  0.290f,  0.734f,
		0.722f,  0.645f,  0.174f,
		0.302f,  0.455f,  0.848f,
		0.225f,  0.587f,  0.040f,
		0.517f,  0.713f,  0.338f,
		0.053f,  0.959f,  0.120f,
		0.393f,  0.621f,  0.362f,
		0.673f,  0.211f,  0.457f,
		0.820f,  0.883f,  0.371f,
		0.982f,  0.099f,  0.879f
	};

	glGenBuffers(1, &this->colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}

void									Cube::build_texture(void)
{
	GLfloat g_uv_buffer_data[] = {
		0, 1,//back
		1, 0,
		0, 1,
		0, 1,
		1, 0,
		0, 1,

		0, 1,//left
		1, 0,
		0, 1,
		0, 1,
		1, 0,
		0, 1,

		0, 0,//face
		0, 0,
		0, 0.5f,
		0, 0,
		0, 0.5f,
		0, 0,

		0, 1,//right
		0, 1,
		0, 1,
		0, 1,
		0, 1,
		0, 1,

		0, 1,//top
		0, 1,
		0, 1,
		0, 1,
		0, 1,
		0, 1,

		0, 1,//down
		0, 1,
		0, 1,
		0, 1,
		0, 1,
		0, 1
	};

	glGenBuffers(1, &this->uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

void 									Cube::produce(void)
{
	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);


	//vao
	//vbo
	//GEn vao
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	{
		glBindVertexArray(VertexArrayID);

		this->matrixID = glGetUniformLocation(ShaderUtils::instance->get("simple"), "MVP");

		this->build_position();
		//this->build_color();

		this->build_texture();

		// this->Texture = SOIL_load_OGL_texture
		// (
		// 	"assets/textures/brique.png",
		// 	SOIL_LOAD_AUTO,
		// 	SOIL_CREATE_NEW_ID,
		// 	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		// );

		this->TextureID  = glGetUniformLocation(ShaderUtils::instance->get("simple"), "firstTexture");
	}

	//TODO unbind array

}

void									Cube::render( const GLfloat *mvp )
{

	glUseProgram(ShaderUtils::instance->get("simple"));

	glUniformMatrix4fv(this->matrixID, 1, GL_FALSE, mvp);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->Texture);
	glUniform1i(this->TextureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(
		 0,                  // attribute id 0
		 3,                  // vec3
		 GL_FLOAT,           // object type
		 false,              // normalized?
		 0,                  // saut apres lecture du vec3
		 0           		 // offset de depart
	);

	// glEnableVertexAttribArray(1);
	// glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
	// glVertexAttribPointer(
	// 		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
	// 		3,                                // size
	// 		GL_FLOAT,                         // type
	// 		GL_FALSE,                         // normalized?
	// 		0,                                // stride
	// 		(void*)0                          // array buffer offset
	// );


	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);


	//6 faces * 2 (2trirangle/face) * 3 vertex pars triangle
	glDrawArrays(GL_TRIANGLES, 0, (6 * 2) * 3);

	//unbind shaders attributes
	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);

	//unbind buffer and shader
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glUseProgram(0);
}

// ###############################################################

// PUBLIC METHOD #################################################

// ###############################################################

// GETTER METHOD #################################################

// ###############################################################

// SETTER METHOD #################################################

// ###############################################################

// PRIVATE METHOD ################################################

// ###############################################################

// EXCEPTION METHOD ##############################################

// ###############################################################

// EXTERNAL ######################################################

// ###############################################################
