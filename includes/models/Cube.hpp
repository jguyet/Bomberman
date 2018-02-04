// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef CUBE_HPP
# define CUBE_HPP

# include "Bomberman.hpp"

class Cube
{
	public:

		Cube( void );
		Cube(float x, float y, float z, float scale);
		Cube( Cube const & src );
		virtual ~Cube( void );

		Cube &											operator=( Cube const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Cube const & i);


		void									render( const GLfloat *mvp );
		void 									produce(void);
		void 									build_position(void);
		void 									build_color(void);
		void									build_texture(void);

		glm::vec3 pos;
		float scale;

		GLuint									matrixID;
		GLuint									vertexBuffer;
		GLuint									colorbuffer;


		GLuint									Texture;
		GLuint									TextureID;

		GLuint 									uvbuffer;

		float										nuit;
};

#endif