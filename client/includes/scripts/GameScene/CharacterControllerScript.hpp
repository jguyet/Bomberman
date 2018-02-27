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
		int 								bomb = 5;
		int 								power = 5;
		int 								life = 5;
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		bool								has_moved = false;

		float								speed = SPEED;

		long 								lastNetwork = 0;
		glm::vec3							lastPosition_direction;
		glm::vec3							lastPosition;

		bool								collide_with_mi_bomb = false;
		bool								in_mi_bomb = false;
		// ####################################################################
};

typedef void (CharacterControllerScript::*P)(void);

#endif
