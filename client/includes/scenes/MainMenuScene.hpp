#ifndef MAINMENUSCENE_HPP
# define MAINMENUSCENE_HPP

# include "Bomberman.hpp"
# include "ui/MainMenuInterface.hpp"

class MainMenuScene : public Scene
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											MainMenuScene( void );
											MainMenuScene( MainMenuScene const & src );
		virtual								~MainMenuScene( void );
		MainMenuScene &							operator=( MainMenuScene const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, MainMenuScene const & i);
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
		MainMenuInterface					*interface;
		// ####################################################################
};

#endif
