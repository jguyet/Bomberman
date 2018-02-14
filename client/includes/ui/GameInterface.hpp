#ifndef GAMEINTERFACE_HPP
# define GAMEINTERFACE_HPP

# include "Bomberman.hpp"

class GameInterface
{
	public:

		GameInterface( int number_of_player );
		GameInterface( GameInterface const & src );
		virtual ~GameInterface( void );

		GameInterface &						operator=( GameInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, GameInterface const & i);

		void								draw(void);

	private:
		int									number_of_player;
		Canvas								*canvas;

};

#endif
