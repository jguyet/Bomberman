// ------------------------------------------------------------	//
//																//
//																//
// ------------------------------------------------------------	//

#ifndef PRESSKEYH_HPP
# define PRESSKEYH_HPP

# include "Bomberman.hpp"

class PressKeyH : IController
{
	public:

		PressKeyH( void );
		PressKeyH( PressKeyH const & src );
		virtual ~PressKeyH( void );

		PressKeyH &							operator=( PressKeyH const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, PressKeyH const & i);

		void								process( void );


};

#endif
