#ifndef SOLOMENUSCENE_HPP
# define SOLOMENUSCENE_HPP

# include "Bomberman.hpp"
# include "ui/SoloMenuInterface.hpp"

class SoloMenuScene : public Scene , public KeyBoardEventHandler
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											SoloMenuScene( void );
											SoloMenuScene( SoloMenuScene const & src );
		virtual								~SoloMenuScene( void );
		SoloMenuScene &						operator=( SoloMenuScene const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, MainMenuScene const & i);
		// ####################################################################
		// @OVERRIDE Scene ###################################################
		void								calculPhisics(void);
		void								drawGameObjects(void);
		void								loadCurrentLevel();
		// Scene functions and vars ->
		//void								_calculPhisics(void);
		//void								_drawGameObjects(void);
		//GameObject						*newGameObject(void);
		//void								add(GameObject *obj);
		//void								remove(GameObject *obj);
		//std::map<long, GameObject*>		gameObjects;
		//Camera							*camera;
		void								handleUP(unsigned int key);
		// ####################################################################
		// PUBLICS ############################################################
		bool								select_server(void);
		SoloMenuInterface					*interface;
		// ####################################################################
};

#endif
