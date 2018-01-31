#ifndef MOUSE_HPP
# define MOUSE_HPP

# include "Bomberman.hpp"

class Mouse
{
	public:

		static Mouse					*instance;

		static void						cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		static void						mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		Mouse( GLFWwindow *window );
		Mouse( Mouse const & src );
		virtual ~Mouse( void );

		Mouse &							operator=( Mouse const & rhs );
		friend std::ostream &			operator<<(std::ostream & o, Mouse const & i);

		int								getMouseButton(int button);

		int								x;
		int								y;

	private:

		GLFWwindow						*window;
};

#endif
