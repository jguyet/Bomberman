#ifndef GAMESCENE_HPP
# define GAMESCENE_HPP

# include "Bomberman.hpp"
# include "ui/StartGameInterface.hpp"
# include "ui/GameInterface.hpp"
# include "scripts/GameScene/CharacterControllerScript.hpp"
# include "scripts/GameScene/ExplosionControllerScript.hpp"
# include "scripts/GameScene/BombControllerScript.hpp"

#include "models/Map.hpp"
class MapManager;
class GameScene : public Scene
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											GameScene(std::string selected_map);
		virtual								~GameScene( void );
		GameScene &							operator=( GameScene const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, GameScene const & i);
		// ####################################################################
		// @OVERRIDE Scene ###################################################
		void 								StartSolo(void);
		void								calculPhisics(void);
		void								drawGameObjects(void);
		GameObject							*findPlayer(GameObject*);
		GameObject							*findPlayerById(int playerId);
		void								removePlayer(GameObject*);
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
		glm::vec3							topoint;
		GameObject							*current_player;
		std::vector<GameObject*>			players;
		std::vector<GameObject*>			all_player;
		Map									*map;
		MapManager							*mapManager;
		//ui
		GameInterface						*interface;
		StartGameInterface					*startGameInterface;
		// ####################################################################
};

#endif
