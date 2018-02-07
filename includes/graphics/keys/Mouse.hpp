#ifndef MOUSE_HPP
# define MOUSE_HPP

# include "Bomberman.hpp"

class Mouse
{
	public:
		// STATICS #############################################################
		static Mouse					*instance;
		static void						cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		static void						mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		// #####################################################################
		// CANONICAL ###########################################################
										Mouse( GLFWwindow *window );
										Mouse( Mouse const & src );
		virtual							~Mouse( void );
		Mouse &							operator=( Mouse const & rhs );
		friend std::ostream &			operator<<(std::ostream & o, Mouse const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		int								getMouseButton(int button);
		void							process(IController *controller);

		glm::vec2						position;
		glm::vec2						lastPosition;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		GLFWwindow						*window;
		bool							pressedButton[8];
		// #####################################################################
};

#endif
