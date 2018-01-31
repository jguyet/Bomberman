#ifndef KEYBOARD_HPP
# define KEYBOARD_HPP

# include "Bomberman.hpp"

class Keyboard
{
	public:

		static Keyboard			*instance;
		static void				key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


		Keyboard( GLFWwindow *window );
		Keyboard( Keyboard const & src );
		virtual ~Keyboard( void );

		Keyboard &							operator=( Keyboard const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, Keyboard const & i);

		int									getKey(int key);

	private:
		GLFWwindow							*window;
};

#endif
