#ifndef GOOMBACONTROLLERSCRIPT_HPP
# define GOOMBACONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class GoombaControllerScript : public Script
{
	public:
		// STATICS ############################################################
		static std::vector<GoombaControllerScript*> List;
		// ####################################################################
		// CANONICAL ##########################################################
											GoombaControllerScript( void);
											GoombaControllerScript( GoombaControllerScript const & src );
		virtual								~GoombaControllerScript( void );
		GoombaControllerScript &				operator=( GoombaControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, GoombaControllerScript const & i);
		// ####################################################################
		// @OVERRIDE Script ###################################################
		void								Update(void);
		void								OnPreRender(void);
		void								OnEndRender(void);
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

		// std::vector<GoombaControllerScript*>	bomb_l;
		// ####################################################################
};

#endif
