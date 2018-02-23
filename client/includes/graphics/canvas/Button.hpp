#ifndef BUTTON_HPP
# define BUTTON_HPP

# include "Bomberman.hpp"

class Button : public GameObject
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
											Button( void );
											Button( Button const & src );
		virtual								~Button( void );
		Button &							operator=( Button const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Button const & i);
		// ####################################################################
		// PUBLICS ############################################################
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		// ####################################################################
};

#endif
