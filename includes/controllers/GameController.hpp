#ifndef GAMECONTROLLER_HPP
# define GAMECONTROLLER_HPP

# include "Bomberman.hpp"

class GameController : public IController
{
	public:
		// STATICS #############################################################
		// #####################################################################
		// CANONICAL ###########################################################
													GameController( void );
													GameController( GameController const & src );
		virtual										~GameController( void );
		GameController &							operator=( GameController const & rhs );
		friend std::ostream &						operator<<(std::ostream & o, GameController const & i);
		// #####################################################################
		// @OVERRIDE IController ###############################################
		void										process(void);
		void										render(void);
		void										pressKeyBoard(unsigned int key);
		void										pressMouseButton(unsigned int button);
		//Camera									*camera = NULL;
		//bool										loaded = false;
		// #####################################################################
		// PUBLIC ##############################################################
		// #####################################################################
		Map											*map;
	private:
		// PRIVATE #############################################################
		void 										Escape( void );
		void 										pressUp( void );
		void 										pressDown( void );
		void 										pressLeft( void );
		void 										pressRight( void );
		void 										pressSpace( void );


		void						R(void);
		void						L(void);
		void						H(void);
		void						B(void);

		typedef void (GameController::*memberMethod)( void );
		std::map<unsigned int, memberMethod>		keyBoard_map;

		GameObject									*p;
		// #####################################################################
};

#endif
