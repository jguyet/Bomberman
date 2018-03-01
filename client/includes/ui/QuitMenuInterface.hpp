#ifndef QUITMENUINTERFACE_HPP
# define QUITMENUINTERFACE_HPP

# include "graphics/keys/KeyBoard.hpp"
# include "Bomberman.hpp"

class QuitMenuInterface : public UIInterface , public KeyBoardEventHandler
{
	public:

		QuitMenuInterface( void );
		QuitMenuInterface( QuitMenuInterface const & src );
		virtual ~QuitMenuInterface( void );

		QuitMenuInterface &					operator=( QuitMenuInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, QuitMenuInterface const & i);

		void								draw(void);

		void								handleUP(unsigned int key);
	private:
		Canvas									*canvas;
};

#endif
