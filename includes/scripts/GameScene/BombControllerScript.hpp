#ifndef BOMBCONTROLLERSCRIPT_HPP
# define BOMBCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class BombControllerScript : public Script
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											BombControllerScript( void );
											BombControllerScript( BombControllerScript const & src );
		virtual								~BombControllerScript( void );
		BombControllerScript &				operator=( BombControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, BombControllerScript const & i);
		// ####################################################################
		// @OVERRIDE Script ###################################################
		void								Update(void);
		//bool								collide = false;
		//std::vector<GameObject*>			colliders;
		// ####################################################################
		// PUBLICS ############################################################
		void								explode(void);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		long								startTime;
		// ####################################################################
};

#endif
