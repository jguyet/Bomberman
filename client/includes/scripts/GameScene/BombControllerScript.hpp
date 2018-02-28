#ifndef BOMBCONTROLLERSCRIPT_HPP
# define BOMBCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class BombControllerScript : public Script
{
	public:
		// STATICS ############################################################
		static std::vector<BombControllerScript*> List;
		// ####################################################################
		// CANONICAL ##########################################################
											BombControllerScript( CharacterControllerScript *playerController);
											BombControllerScript( BombControllerScript const & src );
		virtual								~BombControllerScript( void );
		BombControllerScript &				operator=( BombControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, BombControllerScript const & i);
		// ####################################################################
		// @OVERRIDE Script ###################################################
		void								Update(void);
		void								OnPreRender(void);
		void								OnEndRender(void);
		//bool								collide = false;
		//std::vector<GameObject*>			colliders;
		// ####################################################################
		// PUBLICS ############################################################
		void								explode(void);

		CharacterControllerScript 			*playerController;
		// ####################################################################
		int 								power;
		long								startTime;
	private:
		// PRIVATES ###########################################################
		bool								sens;
		float								max_scale;
		float								min_scale;
		long								anim_time;

		// std::vector<BombControllerScript*>	bomb_l;
		// ####################################################################
};

#endif
