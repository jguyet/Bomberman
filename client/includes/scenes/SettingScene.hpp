#ifndef SETTINGSCENE_HPP
# define SETTINGSCENE_HPP

# include "Bomberman.hpp"
# include "ui/SettingInterface.hpp"
# include "graphics/keys/KeyBoard.hpp"

class SettingScene : public Scene , public KeyBoardEventHandler
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											SettingScene( void );
											SettingScene( SettingScene const & src );
		virtual								~SettingScene( void );

		SettingScene &						operator=( SettingScene const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, SettingScene const & i);
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
		void								handleUP(unsigned int key);
		// ####################################################################
		// PUBLICS ############################################################
		// ####################################################################
	private:
		// PRIVATE ############################################################
		SettingInterface					*interface;
		// ####################################################################

};

#endif
