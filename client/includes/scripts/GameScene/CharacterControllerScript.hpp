#ifndef CHARACTERCONTROLLERSCRIPT_HPP
# define CHARACTERCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class CharacterControllerScript : public Script
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											CharacterControllerScript( void );
											CharacterControllerScript( CharacterControllerScript const & src );
		virtual								~CharacterControllerScript( void );
		CharacterControllerScript &			operator=( CharacterControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, CharacterControllerScript const & i);
		// ####################################################################
		// @OVERRIDE Script ###################################################
		void								Start(void);
		void								Update(void);
		void								OnCollisionEnter(GameObject *collider);
		// PUBLICS ############################################################
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		// ####################################################################
};

#endif
