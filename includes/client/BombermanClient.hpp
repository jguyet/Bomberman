#ifndef BOMBERMANCLIENT_HPP
# define BOMBERMANCLIENT_HPP

# include "Bomberman.hpp"

class BombermanClient : public IRenderLoop
{
	public:
		// STATICS #############################################################
		static BombermanClient						*instance;
		static void									glfw_error_callback( int error, const char* description );
		// #####################################################################
		// CANONICAL ###########################################################
													BombermanClient( void );
													BombermanClient( BombermanClient const & src );
		virtual										~BombermanClient( void );
		BombermanClient &							operator=( BombermanClient const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, BombermanClient const & i);
		// #####################################################################
		// @OVERRIDE ###########################################################
		void										controllerLoop( void );
		void										renderLoop( void );
		// #####################################################################
		// PUBLIC ##############################################################
		void										initialize_properties( void );
		void										initialize_resources( void );
		void										initialize_inputs( void );
		void										build_window( void );
		void										run( void );
		void										stop( void );

		GLFWwindow									*window;
		IController									*currentController;
		// #####################################################################
	private:
		// PRIVATE #############################################################
		RenderLoop									*loop;
		// #####################################################################
};

#endif
