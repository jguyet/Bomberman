#ifndef STARTGAMEINTERFACE_HPP
# define STARTGAMEINTERFACE_HPP

# include "graphics/keys/KeyBoard.hpp"
# include "Bomberman.hpp"

class StartGameInterface : public UIInterface , public KeyBoardEventHandler
{
	public:

		StartGameInterface( void );
		StartGameInterface( StartGameInterface const & src );
		virtual ~StartGameInterface( void );

		StartGameInterface &				operator=( StartGameInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, StartGameInterface const & i);

		void								draw(void);

		void								handleUP(unsigned int key);

	private:
		Canvas									*canvas;
};

#endif
