#ifndef EXPLOSIONCONTROLLERSCRIPT_HPP
# define EXPLOSIONCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class ExplosionControllerScript : public Script
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											ExplosionControllerScript( long timer );
											ExplosionControllerScript( ExplosionControllerScript const & src );
		virtual								~ExplosionControllerScript( void );
		ExplosionControllerScript &			operator=( ExplosionControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, ExplosionControllerScript const & i);
		// ####################################################################
		// @OVERRIDE Script ###################################################
		void								Start(void);
		void								Update(void);
		// PUBLICS ############################################################
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		long								startTime;
		// ####################################################################
		long								start;
		long 								timer;
		long 								timerExplode;

};

#endif
