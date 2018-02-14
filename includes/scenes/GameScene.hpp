#ifndef GAMESCENE_HPP
# define GAMESCENE_HPP

# include "Bomberman.hpp"
# include "scripts/GameScene/CharacterControllerScript.hpp"

class GameScene : public Scene
{
	public:

											GameScene( void );
		virtual								~GameScene( void );

		GameScene &							operator=( GameScene const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, GameScene const & i);

		//override
		void								calculPhisics(void);
		void								drawGameObjects(void);

		GameObject							*player;
		GameInterface						*interface;
		Map									*map;
};

#endif
