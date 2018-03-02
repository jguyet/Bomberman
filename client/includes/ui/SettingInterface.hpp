#ifndef SETTINGINTERFACE_HPP
# define SETTINGINTERFACE_HPP

# include "graphics/keys/KeyBoard.hpp"
# include "Bomberman.hpp"

class SettingInterface : public UIInterface, public KeyBoardEventHandler
{
	public:

											SettingInterface( void );
											SettingInterface( SettingInterface const & src );
		virtual								~SettingInterface( void );

		SettingInterface &					operator=( SettingInterface const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, SettingInterface const & i);

		void								draw(void);
		void								handleUP(unsigned int key);

		int									current_position;
	private:
		Canvas								*canvas;
};

#endif
