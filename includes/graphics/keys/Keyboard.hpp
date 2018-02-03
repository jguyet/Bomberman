#ifndef KEYBOARD_HPP
# define KEYBOARD_HPP

# include "Bomberman.hpp"

class KeyBoard
{
	public:

		static KeyBoard			*instance;
		static void				key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


		KeyBoard( GLFWwindow *window );
		KeyBoard( KeyBoard const & src );
		virtual ~KeyBoard( void );

		KeyBoard &							operator=( KeyBoard const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, KeyBoard const & i);

		bool								getKey(unsigned int key);
		void								process( void );

	private:
		GLFWwindow							*window;
		bool								pressedKeys[301];
};

#endif
