#ifndef MAINMENUINTERFACE_HPP
# define MAINMENUINTERFACE_HPP

# include "Bomberman.hpp"

class MainMenuInterface
{
	public:

											MainMenuInterface( void );
											MainMenuInterface( MainMenuInterface const & src );
		virtual								~MainMenuInterface( void );

		MainMenuInterface &					operator=( MainMenuInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, MainMenuInterface const & i);

		void								draw(void);

		Text								*input_lbl;
	private:
		int									current_position;
		Canvas								*canvas;
};

#endif
