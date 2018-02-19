#ifndef CHARACTERCONTROLLERSCRIPT_HPP
# define CHARACTERCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class CharacterControllerScript : public Script
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											CharacterControllerScript( int n );
											CharacterControllerScript( CharacterControllerScript const & src );
		virtual								~CharacterControllerScript( void );
		CharacterControllerScript &			operator=( CharacterControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, CharacterControllerScript const & i);
		// ####################################################################
		// @OVERRIDE Script ###################################################
		void								Start(void);
		void								Update(void);
		void								OnPreRender(void);
		void								OnEndRender(void);
		void								OnCollisionEnter(GameObject *collider);
		// PUBLICS ############################################################
		void								Attack(void);
		void								MUp(void);
		void								MDown(void);
		void								MLeft(void);
		void								MRight(void);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		long								walk_anim_time;
		int									walk_anim_frame = 0;
		bool								walk_anim = false;

		bool								has_moved = false;
		int 								player = 1;
		// ####################################################################
};

typedef void (CharacterControllerScript::*P)(void);

#endif
