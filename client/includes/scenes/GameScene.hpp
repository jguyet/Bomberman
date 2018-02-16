#ifndef GAMESCENE_HPP
# define GAMESCENE_HPP

# include "Bomberman.hpp"
# include "ui/GameInterface.hpp"
# include "scripts/GameScene/CharacterControllerScript.hpp"
# include "scripts/GameScene/ExplosionControllerScript.hpp"
# include "scripts/GameScene/BombControllerScript.hpp"

#include "models/Map.hpp"
class GameScene : public Scene
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											GameScene( void );
		virtual								~GameScene( void );
		GameScene &							operator=( GameScene const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, GameScene const & i);
		// ####################################################################
		// @OVERRIDE Scene ###################################################
		void								calculPhisics(void);
		void								drawGameObjects(void);
		// Scene functions and vars ->
		//void								_calculPhisics(void);
		//void								_drawGameObjects(void);
		//GameObject						*newGameObject(void);
		//void								add(GameObject *obj);
		//void								remove(GameObject *obj);
		//std::map<long, GameObject*>		gameObjects;
		//Camera							*camera;
		// ####################################################################
		// PUBLICS ############################################################
		GameObject							*player;
		GameObject							*player2;
		GameInterface						*interface;
		Map									*map;
		// ####################################################################
};

#endif
