#ifndef MOUSE_HPP
# define MOUSE_HPP

# include "Bomberman.hpp"

class Mouse
{
	public:
		// STATICS #############################################################
		static Mouse					*instance;
		//static void						cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		//static void						mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		static void							handle_event_mousemotion(SDL_Event *event);
		static void							handle_mousebutton(SDL_Event *event);
		// #####################################################################
		// CANONICAL ###########################################################
										Mouse( void );
										Mouse( Mouse const & src );
		virtual							~Mouse( void );
		Mouse &							operator=( Mouse const & rhs );
		friend std::ostream &			operator<<(std::ostream & o, Mouse const & i);
		// #####################################################################
		// PUBLIC ##############################################################
		bool							getButton(unsigned int button);

		glm::vec2						position;
		glm::vec2						lastPosition;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		bool							pressedButton[8];
		// #####################################################################
};

#endif
