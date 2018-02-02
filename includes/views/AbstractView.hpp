#ifndef IVIEW_HPP
# define IVIEW_HPP

# include "Bomberman.hpp"

class AbstractView
{
	public:
		AbstractView( void );
		AbstractView( AbstractView const & src );
		virtual ~AbstractView( void );
		virtual void render( void );

		AbstractView &							operator=( AbstractView const & rhs );
		friend std::ostream &					operator<<(std::ostream & o, AbstractView const & i);

	protected:
		std::map<unsigned int, IController*>			map;
};

#endif
