#ifndef KEYBOARD_HPP
# define KEYBOARD_HPP

# include "Bomberman.hpp"

class KeyBoard
{
	public:
		// STATICS #############################################################
		static KeyBoard						*instance;
		static void							key_callback(SDL_Event *event);
		// #####################################################################
		// CANONICAL ###########################################################
											KeyBoard( void );
											KeyBoard( KeyBoard const & src );
		virtual								~KeyBoard( void );
		KeyBoard &							operator=( KeyBoard const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, KeyBoard const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		bool								getKey(unsigned int key);
		// #####################################################################
		// #####################################################################
	private:
		// PRIVATE #############################################################
		bool								pressedKeys[301];
		// #####################################################################
};

#endif
