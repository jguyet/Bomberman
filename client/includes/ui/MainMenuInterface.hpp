#ifndef MAINMENUINTERFACE_HPP
# define MAINMENUINTERFACE_HPP


# include "graphics/keys/KeyBoard.hpp"
# include "Bomberman.hpp"

class MainMenuInterface : public UIInterface , public KeyBoardEventHandler
{
	public:

											MainMenuInterface( void );
											MainMenuInterface( MainMenuInterface const & src );
		virtual								~MainMenuInterface( void );

		MainMenuInterface &					operator=( MainMenuInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, MainMenuInterface const & i);

		void								handleUP(unsigned int key);

		void								draw(void);
	private:
		int									current_position;
		Canvas								*canvas;
};

#endif
