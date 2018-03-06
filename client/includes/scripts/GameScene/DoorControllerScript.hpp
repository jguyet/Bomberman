#ifndef DOORCONTROLLERSCRIPT_HPP
# define DOORCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class DoorControllerScript : public Script
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											DoorControllerScript();
											DoorControllerScript( DoorControllerScript const & src );
		virtual								~DoorControllerScript( void );
		DoorControllerScript &				operator=( DoorControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, DoorControllerScript const & i);
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
};
#endif
