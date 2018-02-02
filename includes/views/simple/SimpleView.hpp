#ifndef SIMPLEVIEW_HPP
# define SIMPLEVIEW_HPP

# include "Bomberman.hpp"
# include "views/simple/macrocontrollers/PressKeyH.hpp"

class SimpleView : public AbstractView
{
	public:

		SimpleView( void );
		SimpleView( SimpleView const & src );
		virtual ~SimpleView( void );

		SimpleView &							operator=( SimpleView const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, SimpleView const & i);

		void									render( void );

};

#endif
