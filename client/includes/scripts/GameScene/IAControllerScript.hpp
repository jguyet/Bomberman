#ifndef IACONTROLLERSCRIPT_HPP
# define IACONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class AI;
class IAControllerScript : public Script
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											IAControllerScript( int playerId );
											IAControllerScript( IAControllerScript const & src );
		virtual								~IAControllerScript( void );
		IAControllerScript &			operator=( IAControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, IAControllerScript const & i);
		// ####################################################################
		// @OVERRIDE Script ###################################################
		void								Start(void);
		void								Update(void);
		void								OnPreRender(void);
		void								OnEndRender(void);
		virtual void						OnCollisionEnter(GameObject *collider);
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
		int 								bomb = 1;
		int 								power = 2;
		int 								life = 5;
		int									speed_count = 1;
		float								speed = SPEED;

		bool								locked = false;
		bool								lock_direction[4];
		AI 									*robot;
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

typedef void (IAControllerScript::*P)(void);

#endif
