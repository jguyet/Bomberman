#ifndef ENDGAMESCENE_HPP
# define ENDGAMESCENE_HPP

# include "Bomberman.hpp"
# include "ui/EndGameInterface.hpp"

class EndGameScene : public Scene, public KeyBoardEventHandler
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											EndGameScene( void );
											EndGameScene( EndGameScene const & src );
		virtual								~EndGameScene( void );
		EndGameScene &						operator=( EndGameScene const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, EndGameScene const & i);
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
		void								handleUP(unsigned int key);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		EndGameInterface					*interface;
		// ####################################################################
};

#endif
