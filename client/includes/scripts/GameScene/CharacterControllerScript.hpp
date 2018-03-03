#ifndef CHARACTERCONTROLLERSCRIPT_HPP
# define CHARACTERCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

enum e_direction {
	DIRECTION_RIGHT = 0,
	DIRECTION_LEFT = 1,
	DIRECTION_FORWARD = 2,
	DIRECTION_BACKWARD = 3
};

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
		int									speed_count = 1;
		float								speed = SPEED;

		bool								locked = false;
		bool								lock_direction[4];
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		void								unlockCharacterDirections(void);

		bool								has_moved = false;

		long 								lastNetwork = 0;
		glm::vec3							lastPosition_direction;
		glm::vec3							lastPosition;

	protected:
		GameScene							*scene;
		// ####################################################################
};

typedef void (CharacterControllerScript::*P)(void);

#endif
