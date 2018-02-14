#ifndef CHARACTERCONTROLLERSCRIPT_HPP
# define CHARACTERCONTROLLERSCRIPT_HPP

# include "Bomberman.hpp"

class CharacterControllerScript : public Script
{
	public:

		CharacterControllerScript( void );
		CharacterControllerScript( CharacterControllerScript const & src );
		virtual ~CharacterControllerScript( void );

		CharacterControllerScript &			operator=( CharacterControllerScript const & rhs );
		friend std::ostream &				operator<<(std::ostream & o, CharacterControllerScript const & i);

		void								Update(void);
};

#endif
