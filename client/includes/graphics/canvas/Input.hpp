#ifndef INPUT_HPP
# define INPUT_HPP

# include "graphics/keys/KeyBoard.hpp"
# include "Bomberman.hpp"

class Input : public GameObject, public KeyBoardEventHandler
{
	public:
		// STATICS ############################################################
		// ####################################################################
		// CANONICAL ##########################################################
										Input( void );
										Input( Input const & src );
		virtual							~Input( void );
		Input &							operator=( Input const & rhs );
		friend std::ostream &			operator<<(std::ostream & o, Input const & i);
		// ####################################################################
		// PUBLICS ############################################################
		void							handleUP(unsigned int key);
		void							handleDOWN(unsigned int key);
		void							handleRELEASE(unsigned int key);
		// ####################################################################
	private:
		// PRIVATES ###########################################################
		Button							*button;
		// ####################################################################
};

#endif
