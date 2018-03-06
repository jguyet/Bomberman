#ifndef ENDGAMEINTERFACE_HPP
# define ENDGAMEINTERFACE_HPP

# include "Bomberman.hpp"

class EndGameInterface : public UIInterface
{
	public:

		EndGameInterface( bool is_winner );
		EndGameInterface( EndGameInterface const & src );
		virtual ~EndGameInterface( void );

		EndGameInterface &					operator=( EndGameInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, EndGameInterface const & i);

		void								draw(void);

	private:
		Canvas									*canvas;
		bool									is_winner;

};

#endif
