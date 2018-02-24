#ifndef CHARACTERCONTROLLERSCRIPT_HPP
# define CHARACTERCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class CharacterControllerScript : public Script
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											CharacterControllerScript( int playerId );
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

		void 								BombExplode();
		int 								getPower();
		int									getPlayerId();

		int 								playerId = 1;
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		bool								has_moved = false;

		float								speed = SPEED;
		int 								bomb = 5;
		int 								power = 5;
		int 								life = 5;

		long 								lastNetwork = 0;
		glm::vec3							lastPosition;
		// ####################################################################
};

typedef void (CharacterControllerScript::*P)(void);

#endif
