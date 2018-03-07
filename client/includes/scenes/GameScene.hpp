#ifndef GAMESCENE_HPP
# define GAMESCENE_HPP

# include "Bomberman.hpp"
# include "ui/StartGameInterface.hpp"
# include "ui/EndGameInterface.hpp"
# include "ui/GameInterface.hpp"
# include "ui/QuitMenuInterface.hpp"
# include "scripts/GameScene/CharacterControllerScript.hpp"
# include "scripts/GameScene/ExplosionControllerScript.hpp"
# include "scripts/GameScene/BombControllerScript.hpp"
# include "scripts/GameScene/BotControllerScript.hpp"
# include "scripts/GameScene/DoorControllerScript.hpp"
# include "scripts/GameScene/BonusControllerScript.hpp"


#include "models/Map.hpp"
class MapManager;
class SaveManager;
class GameScene : public Scene, public KeyBoardEventHandler
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
		// @OVERRIDE Scene ####################################################
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
		void 								StartSolo(void);
		GameObject							*findPlayer(GameObject*);
		GameObject							*findPlayerById(int playerId);
		void								removePlayer(GameObject*);
		void								closeQuitInterface(void);
		void								openQuitInterface(void);
		void								build_camera(void);
		void								move_camera(void);
		void								endGame(bool is_winner);
		void								startGame(void);
		void								openEndGameInterface(bool is_winner);

		void								handleUP(unsigned int key);

		glm::vec3							topoint;
		GameObject							*current_player;
		std::vector<GameObject*>			players;
		std::vector<GameObject*>			all_player;
		Map									*map;
		MapManager							*mapManager;
		//ui
		GameInterface						*interface;
		StartGameInterface					*startGameInterface;
		QuitMenuInterface					*quitInterface;
		// ####################################################################
};

#endif
