#ifndef CREDITSCENE_HPP
# define CREDITSCENE_HPP

# include "Bomberman.hpp"
# include "ui/CreditInterface.hpp"

class CreditScene : public Scene, public KeyBoardEventHandler
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											CreditScene( void );
											CreditScene( CreditScene const & src );
		virtual								~CreditScene( void );

		CreditScene &						operator=( CreditScene const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, CreditScene const & i);
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
		CreditInterface					*interface;
		// ####################################################################

};

#endif
