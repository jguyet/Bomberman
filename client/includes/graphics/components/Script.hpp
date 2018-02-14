#ifndef SCRIPT_HPP
# define SCRIPT_HPP

# include "Bomberman.hpp"

class Script : public Component
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Script( void );
											Script( Script const & src );
		virtual								~Script( void );
		Script &							operator=( Script const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Script const & i);
		// ####################################################################
		// @OVERRIDE Component ################################################
		// ####################################################################
		// PUBLICS ############################################################
		//Start is called before the first frame update only if the script instance is enabled.
		virtual void						Start(void);
		//Update is called once per phisic frame. It is the main workhorse function for frame updates.
		virtual void						Update(void);
		//Called before drawing GameObject (WARNING PLEASE NO DELETION HERE)
		virtual void						OnPreRender(void);
		//Called after drawing GameObject (WARNING PLEASE NO DELETION HERE)
		virtual void						OnEndRender(void);
		//Called by Component BoxCollider if have Component<Collider> and it collide with other Object
		virtual void						OnCollisionEnter(GameObject *collider);

		//RESERVED
		long								frame = 0;
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		// ####################################################################
};

#endif
