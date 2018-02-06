#ifndef SIMPLEVIEW_HPP
# define SIMPLEVIEW_HPP

# include "Bomberman.hpp"

class SimpleView : public IView
{
	public:

		SimpleView( void );
		SimpleView( SimpleView const & src );
		virtual ~SimpleView( void );

		SimpleView &								operator=( SimpleView const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, SimpleView const & i);

		void										render( void );

		void 										Escape( void );
		void 										pressUp( void );
		void 										pressDown( void );
		void 										pressLeft( void );
		void 										pressRight( void );
		void 										pressSpace( void );

		void										pressKeyBoard(unsigned int key) {
			if (this->keyBoard_map.count(key) == 1) {
				(this->*keyBoard_map[key])();
			}
		}

	private:
			typedef void (SimpleView::*memberMethod)( void );

			std::map<unsigned int, memberMethod>	keyBoard_map;
			GLuint									matrixID;
			GLuint									vertexBuffer;
			GLuint									colorbuffer;
			std::map<unsigned int, Model*>			models;

			std::vector<Cube*> 			components;

};

#endif
