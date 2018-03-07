#ifndef BotControllerScript_HPP
# define BotControllerScript_HPP

# include "Bomberman.hpp"

class BotControllerScript : public CharacterControllerScript
{
	public:
		// STATICS ############################################################
		static std::vector<BotControllerScript*> List;
		// ####################################################################
		// CANONICAL ##########################################################
											BotControllerScript( int level );
											BotControllerScript( BotControllerScript const & src );
		virtual								~BotControllerScript( void );
		BotControllerScript &				operator=( BotControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, BotControllerScript const & i);
		// ####################################################################
		// @OVERRIDE Script ###################################################
		void								Start(void);
		void								Update(void);
		void								OnPreRender(void);
		//void								OnEndRender(void);
		//void								OnCollisionEnter(GameObject *collider);
		//bool								collide = false;
		//std::vector<GameObject*>			colliders;
		// ####################################################################
		// PUBLICS ############################################################


		// ####################################################################
		int 								power;
		long								startTime;
	private:
		// PRIVATES ###########################################################
		bool								sens;
		float								max_scale;
		float								min_scale;
		long								anim_time;

		int 								level;
		// std::vector<BotControllerScript*>	bomb_l;
		// ####################################################################
};

#endif
