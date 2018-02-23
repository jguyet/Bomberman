#ifndef KEYBOARD_HPP
# define KEYBOARD_HPP

# include "Bomberman.hpp"

struct KeyBoardEventHandler {

	virtual	void							handleUP(unsigned int key) {};
	virtual	void							handleDOWN(unsigned int key) {};
	virtual	void							handleRELEASE(unsigned int key) {};
};

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
		void								addHandler(const char *key, KeyBoardEventHandler *handler);
		void								removeHandler(const char *key);
		// #####################################################################
		// #####################################################################
	private:
		// PRIVATE #############################################################
		std::map<const char*, KeyBoardEventHandler*>	handlers;
		bool											pressedKeys[301];
		// #####################################################################
};

#endif
