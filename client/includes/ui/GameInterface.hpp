#ifndef GAMEINTERFACE_HPP
# define GAMEINTERFACE_HPP

# include "Bomberman.hpp"
class GameScene;
class GameInterface : public UIInterface
{
	public:

		GameInterface( GameScene *scene );
		GameInterface( GameInterface const & src );
		virtual ~GameInterface( void );

		GameInterface &						operator=( GameInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, GameInterface const & i);

		void								draw(void);

	private:
		Canvas								*canvas;
		GameScene							*scene;

};

#endif
